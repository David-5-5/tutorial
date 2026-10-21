import torch

# A, B, output are tensors on the GPU
def solve(A: torch.Tensor, B: torch.Tensor, output: torch.Tensor, N: int):
    idx = torch.arange(2 * N, device=output.device)
    output[(idx % 2) == 0] = A
    output[(idx % 2) == 1] = B

A = torch.tensor([1.0, 2.0, 3.0])
B = torch.tensor([4.0, 5.0, 6.0])
output = torch.zeros(6)
solve(A, B, output, 3)
print(output)