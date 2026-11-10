import torch


# Q, K_int8, V_int8, k_scale, v_scale, output are tensors on the GPU
def solve(
    Q: torch.Tensor,
    K_int8: torch.Tensor,
    V_int8: torch.Tensor,
    k_scale: torch.Tensor,
    v_scale: torch.Tensor,
    output: torch.Tensor,
    num_heads: int,
    seq_len: int,
    head_dim: int,
):
    Q = Q.reshape(num_heads, 1, head_dim)   
    K_int8 = K_int8.reshape(num_heads, seq_len, head_dim)
    V_int8 = V_int8.reshape(num_heads, seq_len, head_dim)
    k_scale = k_scale.reshape(num_heads, seq_len, 1)
    v_scale = v_scale.reshape(num_heads, seq_len, 1)
    kf_t = (K_int8 * k_scale).transpose(1, 2)
    vf = V_int8 * v_scale
    div = torch.sqrt(torch.tensor(head_dim, device=Q.device, dtype=Q.dtype))
    result = torch.matmul(torch.softmax(
        Q.matmul(kf_t)/div,
        dim=2, dtype=Q.dtype), vf)
    output[:] = result.squeeze(1)

num_heads, seq_len, head_dim = 1, 3, 4
Q = torch.tensor([1, 1, 1, 1], dtype=torch.float32)                          # (4,)
K_int8 = torch.tensor([10, 0, 0, 0, 0, 10, 0, 0, 0, 0, 10, 0], dtype=torch.int8)  # (12,) 扁平化
V_int8 = torch.tensor([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120], dtype=torch.int8)  # (12,) 扁平化
k_scale = torch.tensor([0.1, 0.1, 0.1], dtype=torch.float32)                  # (3,)
v_scale = torch.tensor([0.1, 0.1, 0.1], dtype=torch.float32)                  # (3,)
output = torch.zeros(num_heads * head_dim, dtype=torch.float32)                # (4,)

solve(Q, K_int8, V_int8, k_scale, v_scale, output, num_heads, seq_len, head_dim)

print(output)