from typing import List

# 数学问题 : 组合
class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        # 算法精讲 倒序枚举，本题正序枚举
        ans = []
        path = []
        def dfs(i:int) -> None:
            # 剪枝，剩余的数字不够
            if len(path) + n - i < k: return 

            if len(path) == k:
                ans.append(path.copy())
                return
            for j in range(i+1, n+1):
                path.append(j)
                dfs(j) # 选择 j 后续的值，组合选择的数字需要按照顺序
                path.pop()
        dfs(0)
        return ans