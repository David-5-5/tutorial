import torch

# positions, masses, forces are tensors on the GPU
def solve(positions: torch.Tensor, masses: torch.Tensor, forces: torch.Tensor, N: int):
    eps2 = 10 ** -6
    # 计算所有粒子对之间的位移向量 Δr = r_j - r_i
    # 形状: (1,N,3) - (N,1,3) → 广播后得到 (N, N, 3)
    # 物理含义: diff[i, j, k] = pos[j, k] - pos[i, k]
    # 即：第 i 个粒子指向第 j 个粒子的三维向量
    # 注意：这里物化了 N×N×3 的巨大中间矩阵！
    diff = positions.unsqueeze(0) - positions.unsqueeze(1)  # (N, N, 3)，利用广播

    # 计算距离平方 r² + ε²
    # 形状: (N, N, 3) → 沿最后一维求和 → (N, N)
    # 物理含义: r2[i,j] = |r_j - r_i|² + ε²
    # sum(dim=-1) 就是对 x²+y²+z² 求和，得到标量距离平方
    r2 = (diff * diff).sum(dim=-1) + eps2       # (N, N)

    # 计算核函数 1/(r²+ε²)^(3/2)
    # 形状: (N, N)
    # 数学等价: rsqrt(x) = 1/sqrt(x)，所以 rsqrt(r2)/r2 = 1/(sqrt(r2)*r2) = 1/(r²+ε²)^(3/2)
    # 这就是引力公式中的分母部分    
    inv_r3 = torch.rsqrt(r2) / r2               # (N, N)

    # 乘以源粒子质量 m_j
    # 形状: (1, N) * (N, N) → 广播后 (N, N)
    # 物理含义: coef[i,j] = m_j / (|r_j-r_i|²+ε²)^(3/2)
    # mass.unsqueeze(0) 是 (1,N)，代表 j 维度的质量；i 维度被广播
    # 注意：分子是 m_j 不是 m_i，对应加速度公式    
    coef = masses.unsqueeze(0) * inv_r3           # (N, N)

    # 加权求和得到每个粒子的净力/加速度
    # 形状: (N,N,1) * (N,N,3) → (N,N,3) → 沿 j 维求和 → (N, 3)
    # 物理含义: force[i,k] = Σ_j coef[i,j] * diff[i,j,k]
    # unsqueeze(-1) 把 (N,N) 变成 (N,N,1) 以便与 (N,N,3) 逐元素相乘
    # sum(dim=1) 就是对所有 j 求和，完成 Σ_{j≠i} 的聚合    
    forces[:] = (coef.unsqueeze(-1) * diff).sum(dim=1)  # (N, 3)
