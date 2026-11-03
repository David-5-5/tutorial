import torch


# X, S, Y are tensors on the GPU
def solve(X: torch.Tensor, S: torch.Tensor, Y: torch.Tensor, M: int, N: int, TILE_SIZE: int):
    si = torch.arange(M, device=X.device) // TILE_SIZE
    sj = torch.arange(N, device=X.device) // TILE_SIZE
    scale = S[si.unsqueeze(1), sj.unsqueeze(0)]
    Y[:] = X * scale

X = torch.tensor([
  [10, 10,  5,  5],
  [10, 10,  5,  5],
  [ 2,  2,  8,  8],
  [ 2,  2,  8,  8]
])
S = torch.tensor([
  [0.5, 2.0],
  [4.0, 0.25]
])
Y = torch.zeros(4, 4)
solve(X, S, Y, 4, 4, 2)
print(Y)
