from typing import List
# refer to python/dsaa/backtracing.py
class Solution:
    # 使用回溯子集型回溯的模板二
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

    # 使用回溯子集型回溯的模板一
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)

        def dfs(pre:str, i:int):
            if i+1 == n:
                if pre == pre[::-1]:
                    path.append(pre)
                    ans.append(path.copy())
                    path.pop()
                return
            
            # 不选
            dfs(pre+s[i+1], i+1)

            # 选
            if pre == pre[::-1]:
                path.append(pre)
                dfs(s[i+1], i+1)
                path.pop() # 恢复现场，回溯

        dfs(s[0], 0)
        return ans

