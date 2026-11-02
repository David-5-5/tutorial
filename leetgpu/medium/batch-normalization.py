import torch


# input, gamma, beta, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    gamma: torch.Tensor,
    beta: torch.Tensor,
    output: torch.Tensor,
    N: int,
    C: int,
    eps: float,
):
    input.reshape(N, C)
    u = input.sum(dim=0) / N
    sigma = (input - u).pow(2).sum(dim=0) / N
    hat_x = (input - u) / (sigma + eps).pow(0.5)

    output[:] = gamma * hat_x + beta


input = torch.tensor([[1.0, 2.0], [3.0, 4.0], [5.0, 6.0]])
gamma = torch.tensor([1.0, 1.0])
beta = torch.tensor([0.0, 0.0])
output = torch.zeros(input.shape)

solve(input, gamma, beta, output, 3, 2, 1e-5)
print(output)