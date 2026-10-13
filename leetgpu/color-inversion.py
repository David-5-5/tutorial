import torch


# image is a tensor on the GPU
def solve(image: torch.Tensor, width: int, height: int):
    image.bitwise_xor_(255)
    idx = torch.arange(image.numel(), device=image.device)
    print(idx)
    mask = (idx % 4) == 3
    image[mask] ^= 255

def solve2(image: torch.Tensor, width: int, height: int):
    idx = torch.arange(image.numel(), device=image.device)
    mask = (idx % 4) != 3
    # image[mask] = 255 - image[mask]
    image[mask] ^= 255

def solve3(image: torch.Tensor, width: int, height: int):
    n_pixel = width * height
    rgba = image.reshape(n_pixel, 4)
    rgba[:, :3] = 255 - rgba[:, :3]

def solve4(image: torch.Tensor, width: int, height: int):
    # wrong, TLE
    for i in range(image.numel()):
        if i%4 !=3:
            image[i] = 255 - image[i]

image = torch.tensor([255, 0, 128, 255, 0, 255, 0, 255])
solve(image, 1, 2)
print(image)