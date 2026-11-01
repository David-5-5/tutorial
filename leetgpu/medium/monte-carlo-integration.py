import torch


# y_samples, result are tensors on the GPU
def solve(y_samples: torch.Tensor, result: torch.Tensor, a: float, b: float, n_samples: int):
    result[:] = y_samples.sum() * (b - a) / n_samples


y_samples = torch.tensor([0.0625, 0.25, 0.5625, 1.0, 1.5625, 2.25, 3.0625, 4.0])
result = torch.zeros(1, )
solve(y_samples, result, 0, 2, 8)
print(result)
