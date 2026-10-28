import torch


# A, B, result are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, result: torch.Tensor, N: int):
    result[:] = torch.sum(A * B)

A = torch.tensor([1.0, 2.0, 3.0, 4.0])
B = torch.tensor([5.0, 6.0, 7.0, 8.0])
result = torch.zeros(1, )
solve(A, B, result, 4)
print(result)
