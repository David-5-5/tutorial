from functools import cache
from typing import List

class Solution:
    # 同 131
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)
        # 不能 cache ！！！
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

if __name__ == "__main__":
    sol = Solution()
    s = "aab"
    print(sol.partition(s))