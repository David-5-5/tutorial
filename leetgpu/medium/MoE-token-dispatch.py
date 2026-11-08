import torch


# x, expert_idx, dispatched_x, token_counts are tensors on the GPU
def solve(
    x: torch.Tensor,
    expert_idx: torch.Tensor,
    dispatched_x: torch.Tensor,
    token_counts: torch.Tensor,
    T: int,
    D: int,
    E: int,
    capacity: int,
):
    token_counts[:] = torch.bincount(expert_idx, minlength=E)
    for e in range(E):
        mask = expert_idx == e
        dispatched_x[e, :x[mask].shape[0]] = x[mask]


x = torch.tensor([[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 0]])
expert_idx = torch.tensor([0, 1, 0, 1])
dispatched_x = torch.zeros(2, 2, 3)
token_counts = torch.zeros(2, )
solve(x, expert_idx, dispatched_x, token_counts, 4, 3, 2, 4)
print(dispatched_x)
print(token_counts)