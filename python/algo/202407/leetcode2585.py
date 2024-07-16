from functools import cache
from typing import List

# 典型的多重背包问题
# 二进制优化多重背包问题不适用于方案数
class Solution:
    def waysToReachTarget(self, target: int, types: List[List[int]]) -> int:
        # 标准多重背包
        MOD = 10 ** 9 + 7
        n = len(types)
        @cache
        def dfs(i:int, j:int) -> int:
            '''
            i: The i-th question
            j: The left target
            '''
            if i < 0:
                return 1 if j == 0 else 0
            count, marks = types[i]
            # j - k * marks >= 0, k is iterator of count
            # k <= j // marks
            ans = 0
            for k in range(min(count, j//marks)+1):
                ans += dfs(i-1, j-k*marks)
            return ans % MOD
        return dfs(n-1, target)
    
    def waysToReachTarget2(self, target: int, types: List[List[int]]) -> int:
        # 为递推准备，避免数组负数，从 n 到 1
        MOD = 10 ** 9 + 7
        n = len(types)
        @cache
        def dfs(i:int, j:int) -> int:
            '''
            i: The i-th question
            j: The left target
            '''
            if i == 0:
                return 1 if j == 0 else 0
            count, marks = types[i-1]
            # j - k * marks >= 0, k is iterator of count
            # k <= j // marks
            ans = 0
            for k in range(min(count, j//marks)+1):
                ans += dfs(i-1, j-k*marks)
            return ans % MOD
        return dfs(n, target)
    
    def waysToReachTarget3(self, target: int, types: List[List[int]]) -> int:
        # 从 waysToReachTarget2, 将递归一比一翻译成递推
        MOD = 10 ** 9 + 7
        n = len(types)

        f = [[0] * (target + 1) for _ in range(n+1)]
        f[0][0] = 1
        for i in range(1, n+1):
            for j in range(target+1):
                count, marks = types[i-1]
                ans = 0 
                for k in range(min(count, j//marks)+1):
                    ans += f[i-1][j-k*marks] # 直接使用 f[i][j], 删除 ans 变量也是可以的
                f[i][j] = ans % MOD
        return f[-1][-1]

    def waysToReachTarget4(self, target: int, types: List[List[int]]) -> int:
        # 从 waysToReachTarget3, 由于 i 都是从 i-1 状态转移而来，使用一维动态规划
        MOD = 10 ** 9 + 7
        n = len(types)

        f = [0] * (target + 1)
        f[0] = 1
        for i in range(n):
            for j in range(target, -1, -1): 
            # for j in range(target, 0, -1): 这样执行也是通过的
                count, marks = types[i]
                ans = 0 
                for k in range(min(count, j//marks)+1):
                    ans += f[j-k*marks]
                f[j] = ans % MOD
        return f[-1]

    def waysToReachTarget5(self, target: int, types: List[List[int]]) -> int:
        # 从 waysToReachTarget4, 省略 ans 变量的写法
        MOD = 10 ** 9 + 7
        n = len(types)

        f = [0] * (target + 1)
        f[0] = 1
        for count, marks in types:
            for j in range(target, 0, -1):
            # for j in range(target, 0, -1): 这样执行也是通过的
                for k in range(1, min(count, j//marks)+1): # 从 1 开始
                    f[j] += f[j-k*marks]
        return f[-1] % MOD



if __name__ == "__main__":
    sol = Solution()        
    target, types = 6, [[6,1],[3,2],[2,3]]
    print(sol.waysToReachTarget4(target, types))
    print(sol.waysToReachTarget6(target, types))
