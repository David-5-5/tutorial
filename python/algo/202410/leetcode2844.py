from functools import cache
from math import inf


class Solution:
    def minimumOperations(self, num: str) -> int:
        # 自行解答，动态规划 高射炮打蚊子
        n, num = len(num), num[::-1]

        if num == '0': return 0
        @cache
        def dfs(i:int, prev:int):
            if i == n-1:
                if prev == -1: return 1
                if prev == 5 and num[i] in ['2','7']: return 0
                if prev == 0:
                    if num[i] in ['5']: return 0
                    else: return 1
                return 2

            if prev == 5:
                if num[i] in ['2','7']: return 0
                else: return 1 + dfs(i+1, 5)

            if prev == 0 :
                if num[i] in ['0','5']: return 0
                else: return 1 + dfs(i+1, 0)

            res = inf
            if prev == -1:
                res = 1 + dfs(i+1, -1) # 删除不选
                if num[i] == '5': res = min(res, dfs(i+1, 5)) # 选择5
                if num[i] == '0': res = min(res, dfs(i+1, 0)) # 选择0
            
            return res
        
        return dfs(0, -1)
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumOperations("10"))