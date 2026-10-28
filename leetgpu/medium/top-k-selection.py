import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, k: int):
    output[:] = input.topk(k).values


input = torch.tensor([1.0, 5.0, 3.0, 2.0, 4.0])
k = 3
output = torch.zeros(k, )
solve(input, output, 5, k)
print(output)
