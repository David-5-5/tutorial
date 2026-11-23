import torch


# input, weight, bias, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    weight: torch.Tensor,
    bias: torch.Tensor,
    output: torch.Tensor,
    N: int,
    C: int,
    eps: float,
):
    mu = input.mean(dim=1, keepdim=True)
    sigma = input.var(dim=1, keepdim=True, correction=0)
    output[:] = weight * (input - mu)/(sigma+eps).pow(0.5) + bias


N, C, eps = 2, 4, 10 ** -5
input = torch.tensor([[1.0, 2, 3, 4], [-1.0, 0, 0, 1.0]])
weight = torch.tensor([1.0, 1, 1, 1]).reshape(1, C)
bias = torch.tensor([0.0, 0, 0, 0]).reshape(1, C)
output = torch.zeros(N, C)
solve(input, weight, bias, output, N, C, eps)
print(output)


