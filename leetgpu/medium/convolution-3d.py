import torch
import torch.nn.functional as F

# input, kernel, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    kernel: torch.Tensor,
    output: torch.Tensor,
    input_depth: int,
    input_rows: int,
    input_cols: int,
    kernel_depth: int,
    kernel_rows: int,
    kernel_cols: int,
):
    x = input.reshape(1, 1, input_depth, input_rows, input_cols).float()
    w = kernel.reshape(1, 1, kernel_depth, kernel_rows, kernel_cols).float()
    # 执行卷积，默认 stride=1, padding=0
    y = F.conv3d(x, w)
    
    output[:] = y.squeeze(dim=(0,1))


input = torch.tensor([[1, 2, 3, 4, 5, 6, 7, 8, 9]])
kernel = torch.tensor([[0, 1, 1, 0]])
output = torch.zeros(4, )
solve(input, kernel, output, 3, 3, 2, 2)
print(output)
