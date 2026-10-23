import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    mask = input < 0
    input[mask] = 0
    output[:] = input


input = torch.tensor([-2.0, -1.0, 0.0, 1.0, 2.0])
output = torch.zeros(1, 5)
solve(input, output, 5)
print(output)