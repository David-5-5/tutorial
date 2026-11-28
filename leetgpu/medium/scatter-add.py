import torch


# src, index, output are tensors on the GPU
def solve(src: torch.Tensor, index: torch.Tensor, output: torch.Tensor, N: int, D: int, M: int):
    # output.index_add_(0, index, src)
    output.scatter_add_(0, index.unsqueeze(1).expand(-1, D) , src)


N, D, M = 4, 2, 3
src  = torch.tensor([[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 0]])
index  = torch.tensor([[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 0]])
output = torch.tensor([[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 0]])

solve(src, index, output, N, D, M)
print(output)