import torch


# A, B are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, N: int):
    B[:] = A

input = torch.tensor([123, 456, 789])
output = torch.zeros(1, 3)
solve(input, output, 3)
print(output)