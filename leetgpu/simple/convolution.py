import torch
import torch.nn.functional as F

# input, kernel, output are tensors on the GPU
def solve(
    input: torch.Tensor,
    kernel: torch.Tensor,
    output: torch.Tensor,
    input_size: int,
    kernel_size: int,
):
    # x = input.unsqueeze(0).unsqueeze(0)
    # w = kernel.unsqueeze(0).unsqueeze(0)
    # res = F.conv1d(x, w, stride=1, padding=0)
    # output[:] = res.squeeze(0)
    # 1. 构造Conv1d层: Cin=1, Cout=1, kernel_size, stride=1, padding=0
    conv = torch.nn.Conv1d(
        in_channels=1,
        out_channels=1,
        kernel_size=kernel_size,
        stride=1,
        padding=0,
        bias=False
    ).to(input.device)

    # 2. 将传入的kernel设置为conv的weight
    # kernel shape [K] -> weight shape [Cout, Cin, K] = [1,1,K]
    conv.weight = torch.nn.Parameter(kernel.unsqueeze(0).unsqueeze(0)).float()

    # 3. 扩维 input [L] -> [1,1,L] (N,Cin,L)
    x = input.unsqueeze(0).unsqueeze(0).float()

    # 4. 前向计算
    res = conv(x)

    # 5. 原地写入output
    output[:] = res.squeeze(0)

input = torch.tensor([1, 2, 3, 4, 5])
kernel = torch.tensor([1, 0, -1])
output = torch.zeros(1, 3)

solve(input, kernel, output, 5, 3)
print(output)