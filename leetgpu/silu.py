import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    output[:] = input / (1 + torch.exp(-input))
    # output[:] = input * torch.sigmoid(input)

input = torch.tensor([0.5, 1.0, -0.5])
output = torch.zeros(1, 3)
solve(input, output, 3)
print(output)