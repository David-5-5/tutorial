import torch


# logits, probs are tensors on the GPU
def solve(logits: torch.Tensor, probs: torch.Tensor, min_p: float, B: int, V: int):
    pb = torch.softmax(logits, dim=1)
    
    threshlhod = pb < pb.max(dim=1, keepdim=True).values * min_p # p_mask = p_max * min_p

    logits[threshlhod] = -torch.inf # logits.masked_fill_(pb < threshold, -torch.inf)
    probs[:] = torch.softmax(logits, dim=1)


def solve2(logits: torch.Tensor, probs: torch.Tensor, min_p: float, B: int, V: int):
    # deepseek 优化版，一次 softmax
    import math
    l_max = logits.max(dim=1, keepdim=True).values
    
    # 2. 在 Logits 空间算出阈值（不需要做第一次 Softmax！）
    # 加个 max(min_p, 1e-9) 是为了防止 min_p 为 0 时 math.log(0) 报错
    threshold = l_max + math.log(max(min_p, 1e-9))
    
    # 3. 直接比较 Logits 并掩码
    # 避免原地修改输入，用 masked_fill 生成新张量
    masked_logits = logits.masked_fill(logits < threshold, -torch.inf)
    
    # 4. 整个代码全剧终，只做一次 Softmax！
    probs[:] = torch.softmax(masked_logits, dim=1)

min_p, B, V = 0.1, 2, 4
logits = torch.tensor([[1.0, 2.0, 3.0, 4.0], [-1.0, 0.0, 1.0, -2.0]])
probs = torch.zeros(B, V)
solve(logits, probs, min_p, B, V)
print(probs)