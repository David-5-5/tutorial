import torch
import torch.nn.functional as F

# input, output are tensors on the GPU
def solve(input, output, N, C, H, W, kernel_size, stride, padding):
    x = input.reshape(N, C, H, W)
    y = F.max_pool2d(x, kernel_size=kernel_size, stride=stride, padding=padding)
    output[:] = y.reshape(-1)


def solve2(input, output, N, C, H, W, kernel_size, stride, padding):
    # 手写方案，TLE
    x = input.reshape(N, C, H, W)
    pad = padding
    x = F.pad(x, (pad, pad, pad, pad), mode="constant", value=-1e30)

    H_out = (H + 2 * pad - kernel_size) // stride + 1
    W_out = (W + 2 * pad - kernel_size) // stride + 1
    y = torch.empty(N, C, H_out, W_out, device=x.device, dtype=x.dtype)

    for n in range(N):
        for c in range(C):
            for h in range(H_out):
                for w in range(W_out):
                    h0 = h * stride
                    w0 = w * stride
                    y[n, c, h, w] = x[n, c, h0:h0+kernel_size, w0:w0+kernel_size].max()

    output[:] = y.reshape(-1)

# input, output are tensors on the GPU
def solve3(input, output, N, C, H, W, kernel_size, stride, padding):
    # 手写方案, 向量化方案：unfold + max, AC
    x = input.reshape(N, C, H, W)
    x = F.pad(x, (padding, padding, padding, padding), mode="constant", value=-1e30)

    # 展开两个空间轴：[N, C, H_out, W_out, kh, kw]
    windows = x.unfold(2, kernel_size, stride).unfold(3, kernel_size, stride)

    # 沿 kh, kw 两维取 max
    y = windows.max(dim=-1).values.max(dim=-1).values
    output[:] = y.reshape(-1)


input = torch.tensor([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0])
output = torch.zeros(4, )
solve3(input, output, 1, 1, 3, 3, 2, 1, 0)
print(output)
