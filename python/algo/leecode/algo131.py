class Solution:
    def partition(self, s: str) :
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            dp[i][i] = True
            if (i>0):
                dp[i][i-1] = True
            for j in range (i+1, n):
                if dp[i+1][j-1] and s[i] == s[j] :
                    dp[i][j] = True
        return self.nextPartition(s, 0, dp)
    
    def nextPartition(self, s:str, begin, dp):
        retValue = []
        if begin == len(s) - 1:
            return [[s[begin:]]]
        for i in range(begin, len(s)):
            if dp[begin][i]:
                if (i == len(s)-1):
                    retValue.append([s[begin:]])
                else: 
                    ret = self.nextPartition(s, i + 1,dp)
                    for part in ret:
                        element = [s[begin:i + 1]] + part
                        retValue.append(element)
        return retValue

    from typing import List
    # refer to python/dsaa/backtracing.py
    # 使用回溯子集型回溯的模板一
    def partition1(self, s: str) -> List[List[str]]:
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
    
    # 使用回溯子集型回溯的模板二
    def partition2(self, s: str) -> List[List[str]]:
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



if __name__ == "__main__":
    sol = Solution()
    s = "aab"
    print(sol.partition1(s))