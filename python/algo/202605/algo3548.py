from typing import List

# 五、思维题 - 5.7 分类讨论
class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        total = sum(sum(r) for r in grid)

        def check(a: List[List[int]]):
            m, n = len(a), len(a[0])

            def f(a: List[List[int]]):
                s, half = {0}, 0
                for i in range(m-1):
                    
                    for j in range(n):
                        half += a[i][j]
                        if i or j in (0, n-1):
                            s.add(a[i][j])
                    if n == 1:
                        if half*2 in (total, total+a[0][0], total+a[i][0]):
                            return True
                        continue
                    if half*2 - total in s:
                        return True
                    if i == 0:
                        s.update(a[i])
                return False
            if f(a): return True
            return f(a[::-1])

        return check(grid) or check(list(zip(*grid)))        