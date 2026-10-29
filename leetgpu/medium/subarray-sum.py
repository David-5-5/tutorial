import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, S: int, E: int):
    output[:] = input[S:E+1].sum()

input = torch.tensor([1, 2, 3, 4, 1])
output = torch.zeros(1, )
solve(input, output, input.size(), 1, 3)
print(output)
