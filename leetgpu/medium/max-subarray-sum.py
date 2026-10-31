import torch
import torch.nn.functional as F

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int, window_size: int):
    # print(input.unfold(0, window_size, 1))
    window = input.unfold(0, window_size, 1).sum(dim=-1)
    output[:] = window.max()

def solve2(input: torch.Tensor, output: torch.Tensor, N: int, window_size: int):
    # 前缀和差分（cumsum，最省内存）
    P = torch.zeros(N + 1, dtype=input.dtype, device=input.device)
    P[1:] = torch.cumsum(input, dim=0)
    window = P[window_size:] - P[:N - window_size + 1]
    output[:] = window.max()

def solve3(input: torch.Tensor, output: torch.Tensor, N: int, window_size: int):
    # conv1d（全 1 核，等价滑动求和） leetgpu 不支持
    x = input.reshape(1, 1, N)
    w = torch.ones(1, 1, window_size, dtype=input.dtype, device=input.device)
    window = F.conv1d(x, w, stride=1, padding=0).reshape(-1)
    output[:] = window.max()

def solve4(input: torch.Tensor, output: torch.Tensor, N: int, window_size: int):
    # 卷积核视角的广播（无循环、无 unfold）
    n_w = N - window_size + 1
    idx = torch.arange(window_size, device=input.device) \
            .reshape(1, window_size) \
            + torch.arange(n_w, device=input.device).reshape(n_w, 1)
    window = input[idx].sum(dim=1)
    output[:] = window.max()

input = torch.tensor([1, 2, 4, 2, 3])
output = torch.zeros(1, )
solve3(input, output, input.numel(), 2)
print(output)
