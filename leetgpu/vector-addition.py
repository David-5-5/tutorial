import torch

# A, B, C are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, C: torch.Tensor, N: int):
    # 写法一
    # C.add_(A)
    # C.add_(B)
    # 写法二
    C[:] = A.add(B)
    # 写法三
    # C[:] = A + B


A = torch.tensor([1.0, 2.0, 3.0, 4.0])
B = torch.tensor([5.0, 6.0, 7.0, 8.0])
C = torch.tensor([0.0, 0.0, 0.0, 0.0])

solve(A, B, C, 4)
print(C)