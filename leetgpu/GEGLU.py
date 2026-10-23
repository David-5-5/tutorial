import math
import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    half = N // 2
    x1, x2 = input[:half], input[half:]
    output[:] = x1 * 0.5 * x2 * (torch.erf(x2/math.sqrt(2)) + 1)

input = torch.tensor([2.0, -1.0, 1.0, 0.5])
output = torch.zeros(2, )
solve(input, output, 4)
print(output)