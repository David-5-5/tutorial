import torch

# predictions, targets, mse are tensors on the GPU
def solve(predictions: torch.Tensor, targets: torch.Tensor, mse: torch.Tensor, N: int):
    mse[:] = torch.sum(torch.pow(predictions-targets, 2)) / N


predictions = torch.tensor([1.0, 2.0, 3.0, 4.0])
targets = torch.tensor([1.5, 2.5, 3.5, 4.5])
mse = torch.zeros(1, )
solve(predictions, targets, mse, 4)
print(mse)
