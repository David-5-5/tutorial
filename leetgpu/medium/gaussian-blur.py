import torch
import torch.nn.functional as F

# input, kernel, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    kernel: torch.Tensor,
    output: torch.Tensor,
    input_rows: int,
    input_cols: int,
    kernel_rows: int,
    kernel_cols: int,
):
    x = input.reshape(1, 1, input_rows, input_cols)
    # 先对 x 执行 padding
    w_pad, h_pad = kernel_cols//2, kernel_rows//2
    x = F.pad(x, (w_pad, w_pad, h_pad, h_pad), mode="constant", value=0)
    w = kernel.reshape(1, 1, kernel_rows, kernel_cols)

    output[:] = F.conv2d(x, w).reshape(-1)

def solve2(
    input: torch.Tensor,
    kernel: torch.Tensor,
    output: torch.Tensor,
    input_rows: int,
    input_cols: int,
    kernel_rows: int,
    kernel_cols: int,
):
    x = input.reshape(1, 1, input_rows, input_cols)
    w = kernel.reshape(1, 1, kernel_rows, kernel_cols)
    
    # 在 conv2d 中 padding
    w_pad, h_pad = kernel_cols//2, kernel_rows//2
    output[:] = F.conv2d(x, w, padding=(h_pad, w_pad)).reshape(-1)

input = torch.tensor([
    [1.0, 2.0, 3.0, 4.0, 5.0],
    [6.0, 7.0, 8.0, 9.0, 10.0],
    [11.0, 12.0, 13.0, 14.0, 15.0],
    [16.0, 17.0, 18.0, 19.0, 20.0],
    [21.0, 22.0, 23.0, 24.0, 25.0]
  ])
kernel = torch.tensor([
    [0.0625, 0.125, 0.0625],
    [0.125, 0.25, 0.125],
    [0.0625, 0.125, 0.0625]
  ])
output = torch.zeros(input.shape[0]*input.shape[1], )

solve2(input, kernel, output, input.shape[0], input.shape[1], kernel.shape[0], kernel.shape[1])
print(output)
