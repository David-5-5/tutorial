import torch

# input, output are tensors on the GPU
def solve(input: torch.Tensor, output: torch.Tensor, N: int):
    m = input.max()
    input -= m      # max trick
    output[:] = torch.exp(input)/torch.exp(input).sum(dim=0, keepdim=True)


def solve2(input: torch.Tensor, output: torch.Tensor, N: int):
    # 安全写法
    m = input.max()
    z = input - m           # 避免原地修改 input
    exp_z = torch.exp(z)    # 昂贵算子，仅计算一次
    output[:] = exp_z/exp_z.sum()

def solve3(input: torch.Tensor, output: torch.Tensor, N: int):
    output[:] = torch.softmax(input, dim=0, dtype=input.dtype)


input = torch.tensor([-10.0, -5.0, 0.0, 5.0, 10.0])
output = torch.zeros(5, )
solve3(input, output, 5)
print(output)