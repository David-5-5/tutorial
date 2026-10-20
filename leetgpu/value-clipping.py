import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, lo: float, hi: float, N: int):
    # 两种写法
    mn_tensor = torch.full((1, N), lo, device=input.device, dtype=input.dtype)
    mx_tensor = torch.full((1, N), hi, device=input.device, dtype=input.dtype)
    output[:] = torch.min(mx_tensor, torch.max(mn_tensor, input))
    # clip 等价于 clamp，是别名
    # output[:] = input.clamp(min=lo, max=hi)

input = torch.tensor([1.5, -2.0, 3.0, 4.5])
output = torch.zeros(1, 4) # output = torch.zeros(4)
solve(input, output, 0.0, 3.5, 4)
print(output)