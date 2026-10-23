import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, rows: int, cols: int):
    output[:] = input.transpose(0, 1)


input = torch.tensor([[1.0, 2.0, 3.0],[4.0, 5.0, 6.0],[7.0, 8.0, 9.0]])
output = torch.zeros(3, 3)

solve(input, output, 3, 3)
print(output)
print(output.shape)