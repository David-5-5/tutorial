import torch
import torch.nn as nn

# logits, true_labels, loss are tensors on the GPU
def solve(logits: torch.Tensor, true_labels: torch.Tensor, loss: torch.Tensor, N: int, C: int):
    # 写法一：套用公式
    target_logits = logits[torch.arange(N, device=logits.device), true_labels]
    loss[:] = (torch.log(torch.sum(torch.exp(logits), dim=1)) - target_logits).mean()

    # 写法二:上层API
    # loss_fn = nn.CrossEntropyLoss()
    # loss[:] = loss_fn(logits, true_labels.long())

logits = torch.tensor([[1.0, 2.0, 0.5], [0.1, 3.0, 1.5]])
true_labels = torch.tensor([1, 1])
loss = torch.zeros(1, )
solve(logits, true_labels, loss, 2, 3)
print(loss)