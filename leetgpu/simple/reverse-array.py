import torch


# input is a tensor on the GPU
def solve(input: torch.Tensor, N: int):
    input.copy_(torch.flip(input, dims=[0]))

input = torch.tensor([1, 2, 3, 4, 5])

solve(input, 5)
print(input)