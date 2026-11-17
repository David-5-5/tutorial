import torch

# advantages, log_pi, log_pi_old, output are tensors on the GPU
def solve(
    advantages: torch.Tensor,
    log_pi: torch.Tensor,
    log_pi_old: torch.Tensor,
    output: torch.Tensor,
    clip_eps: float,
    B: int,
    S: int,
):
    r = torch.exp(log_pi - log_pi_old)
    r_hat = torch.clip(r, 1-clip_eps, 1+clip_eps)
    l_clip = torch.min(r*advantages, r_hat*advantages)    
    output[:] = -torch.sum(l_clip) / (B * S)


B, S, clip_eps = 1, 4, 0.2
advantages = torch.tensor([1.0, -2, 3, -4])
log_pi = torch.log(torch.tensor([1.3, 0.7, 1.1, 0.8]))
log_pi_old = torch.tensor([0, 0, 0, 0])
output = torch.zeros(B, )
solve(advantages, log_pi, log_pi_old, output, clip_eps, B, S)
print(output)