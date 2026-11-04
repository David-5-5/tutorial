import torch

# values, flags, output are tensors on the GPU
def solve(values: torch.Tensor, flags: torch.Tensor, output: torch.Tensor, N: int):
    # TLE
    idx = (flags==1).nonzero(as_tuple=True)[0]
    parts = torch.tensor_split(values, idx.cpu()) # 仅支持 cpu
    parts_cumsum = torch.cat([p.cumsum(0) for p in parts])
    output[:] = parts_cumsum - values

def solve2(values: torch.Tensor, flags: torch.Tensor, output: torch.Tensor, N: int):
    idx = torch.cumsum(flags, dim=0) - 1
    cs = torch.cumsum(values, dim=0)
    seg_sum = torch.zeros_like(cs).scatter_add(0, idx, values)
    offset = torch.cumsum(seg_sum, dim=0) - seg_sum
    parts_cumsum = cs - offset[idx]
    output[:] = parts_cumsum - values
    

values = torch.tensor([1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
flags = torch.tensor([1, 0,  0, 1, 0, 1])
output = torch.zeros(values.numel(), )

solve2(values, flags, output, values.numel())
print(output)

