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


batch, seq_len, d = 1, 2, 2
Q = torch.tensor([[[1.0, 1], [1, 1]]])                        # (4,)
K = torch.tensor([[[1.0, 0], [0, 1]]])                        # (12,) 扁平化
V = torch.tensor([[[1.0, 2], [2, 0]]])                        # (12,) 扁平化
alpha = torch.tensor([[[1.0, 1], [0.5, 0.5]]])                # (3,)
beta = torch.tensor([[1, 0.5]])                              # (3,)
output = torch.zeros(batch, seq_len, d)                            # (4,)

solve(Q, K, V, alpha, beta, output, batch, seq_len, d)

print(output)