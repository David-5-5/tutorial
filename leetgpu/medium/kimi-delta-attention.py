import torch

# Q, K, V, alpha, beta, output are tensors on the GPU
def solve3(
    Q: torch.Tensor,
    K: torch.Tensor,
    V: torch.Tensor,
    alpha: torch.Tensor,
    beta: torch.Tensor,
    output: torch.Tensor,
    batch: int,
    seq_len: int,
    d: int,
):
    C = 64
    num_chunks = (seq_len + C - 1) // C
    pad_len = num_chunks * C - seq_len
    
    if pad_len > 0:
        Q_pad = torch.cat([Q, torch.zeros(batch, pad_len, d, device=Q.device)], dim=1)
        K_pad = torch.cat([K, torch.zeros(batch, pad_len, d, device=K.device)], dim=1)
        V_pad = torch.cat([V, torch.zeros(batch, pad_len, d, device=V.device)], dim=1)
        beta_pad = torch.cat([beta, torch.zeros(batch, pad_len, device=beta.device)], dim=1)
        alpha_pad = torch.cat([alpha, torch.ones(batch, pad_len, d, device=alpha.device)], dim=1)
    else:
        Q_pad, K_pad, V_pad, alpha_pad, beta_pad = Q, K, V, alpha, beta

    Q_chunks = Q_pad.view(batch, num_chunks, C, d)
    K_chunks = K_pad.view(batch, num_chunks, C, d)
    V_chunks = V_pad.view(batch, num_chunks, C, d)
    alpha_chunks = alpha_pad.view(batch, num_chunks, C, d)
    beta_chunks = beta_pad.view(batch, num_chunks, C)

    S = torch.zeros(batch, d, d, device=Q.device, dtype=Q.dtype)
    
    # 单位矩阵，用来解三角方程组
    I = torch.eye(C, device=Q.device, dtype=Q.dtype).unsqueeze(0)
    
    for i in range(num_chunks):
        q_c = Q_chunks[:, i, :, :]
        k_c = K_chunks[:, i, :, :]
        v_c = V_chunks[:, i, :, :]
        a_c = alpha_chunks[:, i, :, :]
        b_c = beta_chunks[:, i] # [B, C]

        # 块内累积衰减
        A_cum = torch.cumprod(a_c, dim=1) # [B, C, d]
        
        # 核心变换：K 和 Q 分别除以/乘以累积衰减
        K_inv = k_c / A_cum
        K_scaled = k_c * A_cum
        Q_scaled = q_c * A_cum
        
        # 1. 计算块内的 Attention 矩阵（包含 Delta 规则的依赖）
        # M 矩阵：捕捉块内各个 token 之间的相互影响
        M = torch.bmm(K_scaled, K_inv.transpose(1, 2)) # [B, C, C]
        
        # 取严格下三角，并乘上 beta（表示误差修正的强度）
        L = torch.tril(M, diagonal=-1) * b_c.unsqueeze(1) 
        
        # 2. 解方程组 (I + L) U = V - K_scaled * S_prev
        # 这是 Delta 规则在块内的数学本质
        RHS = v_c - torch.bmm(K_scaled, S)
        U = torch.linalg.solve_triangular(I + L, RHS, upper=False, unitriangular=True)

        # 3. 计算输出 (Attention Output + 历史状态)
        # 块内 token 之间的关联输出
        Attn = torch.bmm(Q_scaled, K_inv.transpose(1, 2))
        Attn = torch.tril(Attn, diagonal=0)
        intra_out = torch.bmm(Attn, U * b_c.unsqueeze(-1))
        
        # 历史状态的输出 (注意这里用的是没有 K_inv 的 Q)
        inter_out = torch.bmm(Q_scaled, S)
        
        out_c = intra_out + inter_out
        
        # 4. 更新全局状态 S (为下一个 Chunk 准备)
        # 更新公式：S_new = A_cum[-1] * (S_prev + K_inv^T * (beta * U))
        decay_final = A_cum[:, -1, :] # [B, d]
        S_update = torch.bmm(K_inv.transpose(1, 2), U * b_c.unsqueeze(-1))
        S = decay_final.unsqueeze(2) * (S + S_update)

        # 5. 写入输出（带边界保护）
        start = i * C
        end = min((i + 1) * C, seq_len)
        if start < seq_len:
            output[:, start:end, :] = out_c[:, :end - start, :]


def solve(
    Q: torch.Tensor,
    K: torch.Tensor,
    V: torch.Tensor,
    alpha: torch.Tensor,
    beta: torch.Tensor,
    output: torch.Tensor,
    batch: int,
    seq_len: int,
    d: int,
):  
    # 串行执行
    prev_s = torch.zeros(batch, d, d, device=Q.device)
    I = torch.eye(d, device=Q.device).repeat(batch, 1, 1)
    for t in range(seq_len):
        q, k, v = Q[:, t, :], K[:, t, :], V[:, t, :]
        b = beta[:, t].unsqueeze(1).unsqueeze(1)
        a = alpha[:, t, :].unsqueeze(2)

        cur_s = b * k.unsqueeze(2) @ v.unsqueeze(1)
        cur_s += (I - b * k.unsqueeze(2) @ k.unsqueeze(1)) @ (prev_s * a)

        output[:, t, :] = (cur_s.transpose(1, 2) @ q.unsqueeze(2)).squeeze(-1)
        prev_s = cur_s

def solve2(
    Q: torch.Tensor,
    K: torch.Tensor,
    V: torch.Tensor,
    alpha: torch.Tensor,
    beta: torch.Tensor,
    output: torch.Tensor,
    batch: int,
    seq_len: int,
    d: int,
):
    # 串行执行优化版
    prev_s = torch.zeros(batch, d, d, device=Q.device, dtype=Q.dtype)
    
    for t in range(seq_len):
        q = Q[:, t, :]          # [B, d]
        k = K[:, t, :]          # [B, d]
        v = V[:, t, :]          # [B, d]
        b = beta[:, t]          # [B]
        a = alpha[:, t, :]      # [B, d]

        # 1. 计算衰减后的状态 (Row-wise 乘法)
        S_decayed = prev_s * a.unsqueeze(2)  # [B, d, d]

        # 2. 实现 Delta Rule (计算误差项)
        # 原公式 (I - b*k*k^T) 展开后相当于： v - k^T * S_decayed
        # k.unsqueeze(1) 是 [B, 1, d]，S_decayed 是 [B, d, d]
        # bmm 计算结果为 [B, 1, d]
        inner = v.unsqueeze(1) - torch.bmm(k.unsqueeze(1), S_decayed) 
        
        # 3. 加上更新项 b * k * inner
        # k.unsqueeze(2) 是 [B, d, 1]，inner 是 [B, 1, d]
        # bmm 计算结果为 [B, d, d]
        update = b.view(batch, 1, 1) * torch.bmm(k.unsqueeze(2), inner)
        
        # 4. 得到当前状态
        cur_s = S_decayed + update

        # 5. 输出 o_t = S_t^T * q_t
        # 原代码用的是 @，这里统一用 torch.bmm 提高可读性
        output[:, t, :] = torch.bmm(cur_s.transpose(1, 2), q.unsqueeze(2)).squeeze(-1)
        
        # 更新状态
        prev_s = cur_s

batch, seq_len, d = 1, 2, 2
Q = torch.tensor([[[1.0, 1], [1, 1]]])                        # (4,)
K = torch.tensor([[[1.0, 0], [0, 1]]])                        # (12,) 扁平化
V = torch.tensor([[[1.0, 2], [2, 0]]])                        # (12,) 扁平化
alpha = torch.tensor([[[1.0, 1], [0.5, 0.5]]])                # (3,)
beta = torch.tensor([[1, 0.5]])                              # (3,)
output = torch.zeros(batch, seq_len, d)                            # (4,)

solve3(Q, K, V, alpha, beta, output, batch, seq_len, d)

print(output)