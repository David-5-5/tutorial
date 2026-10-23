import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, width: int, height: int):
    # 自行解答
    idx = torch.arange(width * height * 3, device=input.device)
    r, g, b = (idx % 3) == 0, (idx % 3) == 1, (idx % 3) == 2
    output[:] = 0.299 * input[r] + 0.587 * input[g]  + 0.114 * input[b]

def solve2(input: torch.Tensor, output: torch.Tensor, width: int, height: int):
    # reshape/view 分组
    n = width * height
    w = torch.tensor([0.299, 0.587, 0.114], device=input.device, dtype=input.dtype)
    rgb = input.reshape(n, 3) # rgb = input.view(n, 3)
    torch.matmul(rgb, w, out=output) # output[:] = rgb @ w 

def solve3(input: torch.Tensor, output: torch.Tensor, width: int, height: int):
    # chunk 拆分通道
    # r, g, b = torch.chunk(input, 3, dim=0)
    r, g, b = input[0::3], input[1::3], input[2::3]
    output[:] = 0.299 * r + 0.576 * g + 0.114 * b


input = torch.tensor([255.0, 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 255.0, 128.0, 128.0, 128.0])
output = torch.zeros(4, )
solve2(input, output, 2, 2)
print(output)