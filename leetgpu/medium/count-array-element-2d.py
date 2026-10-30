import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, M: int, K: int):
    output[:] = input.eq(K).sum()


input = torch.tensor([[1, 2, 3], [4, 5, 1]])
output = torch.zeros(1, )
solve(input, output, 2, 3, 1)
print(output)
