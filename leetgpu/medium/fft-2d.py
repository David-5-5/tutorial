import torch


# signal, spectrum are tensors on the GPU
def solve(signal: torch.Tensor, spectrum: torch.Tensor, M: int, N: int):
    x = torch.view_as_complex(signal.view(M * N, 2)).view(M, N)
    result = torch.fft.fft2(x)
    spectrum[:] = torch.view_as_real(result).contiguous().view(-1)

signal = torch.tensor([1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
spectrum = torch.zeros(8, )
solve(signal, spectrum, 2, 2)
print(spectrum)

