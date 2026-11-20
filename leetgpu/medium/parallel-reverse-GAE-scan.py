import torch


# rewards, values, advantages are tensors on the GPU
def solve(
    rewards: torch.Tensor,
    values: torch.Tensor,
    advantages: torch.Tensor,
    gamma: float,
    lam: float,
    B: int,
    S: int,
):
    values = values.reshape(B, S)
    v_shift = torch.zeros_like(values, device=rewards.device)
    v_shift[:, :-1] = values[:, 1:]
    delta = rewards + v_shift * gamma - values

    c = gamma * lam
    # 构造对角为 0, 每行递增
    row = torch.arange(S-1, -1, -1, device=rewards.device).reshape(1, S)
    col = torch.arange(S-1, -1, -1, device=rewards.device).reshape(1, S).transpose(0, 1)
    # 取指数后，取矩阵下三角，对角为 1
    tri = torch.tril(torch.pow(c, row - col))

    advantages[:] = delta.matmul(tri)

B, S, gamma, lam = 1, 4, 0.9, 0.5
rewards = torch.tensor([1.0, 2, 3, 4])
values = torch.tensor([0.5, 1, 1.5, 2])
advantages = torch.zeros(B, S)
solve(rewards, values, advantages, gamma, lam, B, S)
print(advantages)