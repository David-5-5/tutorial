import torch

# Q, K, V, alpha, beta, output are tensors on the GPU
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

solve2(Q, K, V, alpha, beta, output, batch, seq_len, d)

print(output)