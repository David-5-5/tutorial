import torch


# X, Y are tensors on the GPU
def solve(X: torch.Tensor, Y: torch.Tensor, N: int):
    # Y[:] = 0.5 * X * (torch.erf(X/math.sqrt(2)) + 1)
    Y[:] = torch.nn.functional.gelu(X)

X = torch.tensor([0.0, 1.0, -1.0, 2.0])
Y = torch.zeros(4, )
solve(X, Y, 4)
print(Y)