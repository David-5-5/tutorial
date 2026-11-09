import torch


# input, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    output: torch.Tensor,
    N: int,
    M: int,
    K: int,
    S_DEP: int,
    E_DEP: int,
    S_ROW: int,
    E_ROW: int,
    S_COL: int,
    E_COL: int,
):
    output[:] = input[S_DEP: E_DEP+1, S_ROW:E_ROW+1, S_COL:E_COL+1].sum()


input = torch.tensor([[[1, 2, 3], [4, 5, 1]], [[1, 1, 1], [2, 2, 2]]])
output = torch.zeros(1, )
solve(input, output, 2, 2, 3, 0, 1, 0, 0, 1, 2)
print(output)
