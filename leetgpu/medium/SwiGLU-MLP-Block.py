import torch


# x, W_gate, W_up, W_down, output are tensors on the GPU
def solve(
    x: torch.Tensor,
    W_gate: torch.Tensor,
    W_up: torch.Tensor,
    W_down: torch.Tensor,
    output: torch.Tensor,
    M: int,
    d_model: int,
    d_ffn: int,
):
    import torch.nn.functional as F
    gate = F.silu(x.matmul(W_gate))
    up = x.matmul(W_up)
    output[:] = (gate * up).matmul(W_down)


x = torch.tensor([[1.0, 0.0], [0.0, 1.0]])
W_gate = torch.tensor([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0]])
W_up = torch.tensor([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0]])
W_down = torch.tensor([[1.0, 0.0], [0.0, 1.0], [0.0, 0.0], [0.0, 0.0]])
output = torch.zeros(2, 2)
solve(x, W_gate, W_up, W_down, output, 2, 2, 4)
print(output)
