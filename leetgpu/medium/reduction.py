import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    output[:] = input.sum()


input = torch.tensor([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0])
output = torch.zeros(1, )
solve(input, output, 8)
print(output)