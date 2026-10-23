import torch
import torch.nn as nn


# input, model, and output are on the GPU
def solve(input: torch.Tensor, model: nn.Module, output: torch.Tensor):
    with torch.no_grad():
        output[:] = model(input)

input = torch.tensor([[[1.0, 2.0]]])
model = nn.Linear(2, 2)
model.weight.data[:] = torch.tensor([[0.5, 1.0],
                                     [1.5, 0.5]])
model.bias.data[:] = torch.tensor([0.1, 0.2])
output = torch.zeros(1, 2)
solve(input, model, output)
print(output)
