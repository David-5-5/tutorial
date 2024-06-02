from typing import List
# 使用回溯子集型回溯的模板二
# refer to python/dsaa/backtracing.py
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)

        def dfs(i):
            if i == n:
                ans.append(path.copy())
                return
            
            for j in range(i,n):
                t = s[i:j+1]
                if t == t[::-1]:
                    path.append(t)
                    dfs(j+1)
                    path.pop() # 恢复现场，回溯

        dfs(0)
        return ans