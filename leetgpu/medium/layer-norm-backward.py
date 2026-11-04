import torch


# x, gamma, mean, rstd, dy, dx, dgamma, dbeta are tensors on the GPU
def solve(
    x: torch.Tensor,
    gamma: torch.Tensor,
    mean: torch.Tensor,
    rstd: torch.Tensor,
    dy: torch.Tensor,
    dx: torch.Tensor,
    dgamma: torch.Tensor,
    dbeta: torch.Tensor,
    N: int,
    C: int,
):
    x_hat = (x - mean.reshape(N, 1)) * rstd.reshape(N, 1)
    g = dy * gamma
    dx[:] = rstd.reshape(N, 1) * (
        g -
        g.sum(dim=1, keepdim=True) / C - 
        x_hat * ((g * x_hat).sum(dim=1, keepdim=True) / C)
    )
    dgamma[:] = (dy * x_hat).sum(dim=0, keepdim=True)
    dbeta[:] = dy.sum(dim=0, keepdim=True)


x = torch.tensor([[1.0, 2.0, 3.0, 4.0], [-1.0, 0.0, 0.0, 0.0]])
gamma = torch.tensor([1.0, 1.0, 1.0, 1.0])
mean = torch.tensor([2.5, 0.0])
rstd = torch.tensor([0.8944, 1.4142])
dy = torch.tensor([[1.0, 1.0, 1.0, 1.0], [1.0, 0.0, 0.0, 1.0]])
dx = torch.zeros(2, 4)
dgamma = torch.zeros(4, )
dbeta = torch.zeros(4, )

solve(x, gamma, mean, rstd, dy, dx, dgamma, dbeta, 2, 4)

print(dx, dgamma, dbeta, sep="\n")
