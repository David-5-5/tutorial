import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, P: int):
    x = input.reshape(N, N)
    output[:] = x.matrix_power(P).reshape(-1)


input = torch.tensor([[1.0, 0.0, 2.0], [0.0, 1.0, 0.0], [3.0, 0.0, 0.0]])
output = torch.zeros(3*3, )
solve(input, output, 3, 2)
print(output)
