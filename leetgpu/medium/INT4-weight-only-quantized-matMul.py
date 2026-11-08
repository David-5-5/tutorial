import torch

# x, w_q, scales, y are tensors on the GPU
def solve(
    x: torch.Tensor,
    w_q: torch.Tensor,
    scales: torch.Tensor,
    y: torch.Tensor,
    M: int,
    N: int,
    K: int,
    group_size: int,
):
    # Optional
    # x.reshape(M, K)
    # w_q.reshape(N, K//2)
    # scales.reshape(N, K//group_size)

    low = (w_q & 0x0F).to(torch.int8)           # 
    high = ((w_q >> 4) & 0x0F).to(torch.int8)
    w_i = torch.stack([high, low], dim=-1).reshape(low.shape[0], -1)

    sj = torch.arange(K, device=scales.device) // group_size
    s = scales[:, sj]
    
    y[:] = x.matmul(((w_i - 8).mul(s)).transpose(0, 1))


x = torch.tensor([
  [1.0, 0.0, 1.0, 0.0],
  [0.0, 1.0, 0.0, 1.0]
])
w_q = torch.tensor([
  [0x99, 0x99],
  [0xAA, 0xAA],
  [0x77, 0x77],
  [0x88, 0x88]
])
scales = torch.tensor([
  [0.5, 0.5],
  [0.5, 0.5],
  [0.5, 0.5],
  [0.5, 0.5]
])
y = torch.zeros(2, 4)
solve(x, w_q, scales, y, 2, 4, 4, 2)
print(y)
