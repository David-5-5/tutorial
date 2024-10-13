# 0-1 背包 模板

from functools import cache
from typing import List

# 背包 容量
# 常见变形
# - 至多装 capacity 求方案数/最大价值和
# - 恰好装 capacity 求方案数/最大/最小价值和
# - 至少装 capacity 求方案数/最小价值和
def zero_one_knapsack(capacity:int, w:List[int], v: List[int])->int:
    n = len(w)
    @cache
    def dfs(i:int, c:int) ->int:
        if i < 0:
            return 0
        if c < w[i]:
            return dfs(i-1,c)
        return max(dfs(i-1,c), dfs(i-1, c-w[i]) + v[i])
    return dfs(n-1, capacity)

def unbounded_knapsack(capacity:int, w:List[int], v: List[int])->int:
    n = len(w)
    @cache
    def dfs(i:int, c:int) ->int:
        if i < 0:
            return 0
        if c < w[i]:
            return dfs(i-1,c)
        return max(dfs(i-1,c), dfs(i, c-w[i]) + v[i])
    return dfs(n-1, capacity)
