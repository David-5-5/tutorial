import torch


# A, B, C are tensors on the GPU
def solve(
    A: torch.Tensor,
    B: torch.Tensor,
    C: torch.Tensor,
    M: int,
    N: int,
    K: int,
    scale_A: float,
    scale_B: float,
    scale_C: float,
    zero_point_A: int,
    zero_point_B: int,
    zero_point_C: int,
):
    scale = scale_A*scale_B/scale_C
    a = A.sub(zero_point_A).reshape(M, K).float()
    b = B.sub(zero_point_B).reshape(K, N).float()
    c = torch.round(a.matmul(b).mul(scale)) + zero_point_C
    C[:] = torch.clamp(c, -128, 127).reshape(C.shape)


A = torch.tensor([[1, 2], [3, 4]])
B = torch.tensor([[5, 6], [7, 8]])
C = torch.zeros(2, 2)

solve(A, B, C, 2, 2, 2, 0.1, 0.2, 0.05, 0, 0, 0)

print(C)
