import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, K: int):
    output[:] = (input[input == K]).numel()
    # 其他写法
    output[:] = (input == K).sum()
    output[:] = torch.eq(input, K).sum()
    output[:] = input.eq(K).sum()
    output[:] = torch.count_nonzero(input == K)

input = torch.tensor([1, 2, 3, 4, 1])
output = torch.zeros(1, )
solve(input, output, input.size(), 1)
print(output)
