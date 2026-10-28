import torch

# X, y, beta are tensors on the GPU
def solve(X: torch.Tensor, y: torch.Tensor, beta: torch.Tensor, n_samples: int, n_features: int):
    x2 = X.reshape(n_samples, n_features)
    xt = x2.transpose(0, 1)
    z = (xt.matmul(x2)).inverse().matmul(xt)
    torch.matmul(z, y, out=beta)


n_samples, n_feature = 5, 3
X = torch.tensor([[-0.23, -0.23, 1.52], [0.77, -0.47, 1.58], [-0.14, 0.65, 0.5], [-1.91, -1.72, 0.24], [-0.46, -0.47, 0.54]])
y = torch.tensor([83.01, 93.4, 47.33, -62.22, 13.06])
beta = torch.zeros(n_feature, )
solve(X, y, beta, n_samples, n_feature)
print(beta)
