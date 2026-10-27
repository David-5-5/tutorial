import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    output[:] = torch.cumsum(input, dim=0)

input = torch.tensor([1.0, 2.0, 3.0, 4.0])
output = torch.zeros(4, )
solve(input, output, 4)
print(output)