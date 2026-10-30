import torch


# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, M: int, K: int, P: int):
    # 逐元素比较，和维度无关，2D 3D 4D 行为一致
    output[:] = input.eq(P).sum()


input = torch.tensor([[[1, 2, 3],  [4, 5, 1]], [[1, 1, 1], [2, 2, 2]]])
output = torch.zeros(1, )
solve(input, output, 2, 2, 3, 1)
print(output)
