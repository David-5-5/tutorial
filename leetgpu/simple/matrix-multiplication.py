import torch


# A, B, C are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, C: torch.Tensor, M: int, N: int, K: int):
    # C[:] = A.matmul(B)
    # C[:] = A @ B
    torch.matmul(A, B, out=C)
    # C[:] = A * B # A.mul(B)



A = torch.tensor([[1.0, 2.0], [3.0, 4.0]])
B = torch.tensor([[5.0, 6.0], [7.0, 8.0]])
C = torch.zeros(2, 2)

solve(A, B, C, 2, 2, 2)
print(C)