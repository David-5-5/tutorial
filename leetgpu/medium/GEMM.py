import torch

# A, B, C are tensors on the GPU
def solve(
    A: torch.Tensor,
    B: torch.Tensor,
    C: torch.Tensor,
    M: int,
    N: int,
    K: int,
    alpha: float,
    beta: float,
):
    C[:] = alpha * A.matmul(B) + beta * C

A = torch.tensor([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]])
B = torch.tensor([[1.0, 2.0], [3.0, 4.0], [5.0, 6.0]])
C = torch.tensor([[1.0, 1.0], [1.0, 1.0]])

solve(A, B, C, 2, 2, 3, 1.0, 0.0)
print(C)
