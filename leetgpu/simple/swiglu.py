import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    half = N // 2
    x1, x2 = input[:half], input[half:]
    output[:] = x1 * torch.sigmoid(x1) * x2

def solve2(input: torch.Tensor, output: torch.Tensor, N: int):
    import torch.nn.functional as F
    half = N // 2
    x1, x2 = input[:half], input[half:]
    output[:] = F.silu(x1) * x2


input = torch.tensor([1.0, 2.0, 3.0, 4.0])
output = torch.zeros(1, 2)
solve2(input, output, 4)
print(output)