import torch


# Q, K, V, output are tensors on the GPU
def solve(
    Q: torch.Tensor, K: torch.Tensor, V: torch.Tensor, output: torch.Tensor, M: int, N: int, d: int
):
    div = torch.sqrt(torch.tensor(d, device=Q.device, dtype=Q.dtype))
    
    torch.matmul(torch.softmax(
        Q.matmul(K.transpose(0, 1))/div,
        dim=1, dtype=Q.dtype), V, out=output)

Q = torch.tensor([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0]])
K = torch.tensor([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]])
V = torch.tensor([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [9.0, 10.0, 11.0, 12.0]])
output = torch.zeros(3, 3)

solve(Q, K, V, output, 2, 3, 4)
print(output)