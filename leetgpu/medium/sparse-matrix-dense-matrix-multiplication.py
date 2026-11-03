import torch


# A, B, C are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, C: torch.Tensor, M: int, N: int, K: int, nnz: int):
    C[:] = A.matmul(B)

A = torch.tensor([[2.0, 0.0, 0.0, 1.0], [0.0, 3.0, 0.0, 0.0], [0.0, 0.0, 4.0, 0.0]])
B = torch.tensor([[1.0, 2.0], [3.0, 4.0], [5.0, 6.0], [7.0, 8.0]])
C = torch.zeros(3, 2)
solve(A, B, C, 3, 4, 2, 4)
print(C)
