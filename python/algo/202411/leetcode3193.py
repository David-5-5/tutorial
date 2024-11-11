from functools import cache
from typing import List

# 双周赛 133
class Solution:
    def numberOfPermutations(self, n: int, requirements: List[List[int]]) -> int:
        # 参考题解
        # 状态转移方程 dp(i, j) += dp(i-1, j-k)
        # 其中  1: dp(i, j) 表示前 i 个数字包含 j 个逆序对的数量
        #       2: i 从 i - 1转移过来，增加了 k 个逆序对
        MOD = 1_000_000_007
        req = [-1] * n
        req = [0]
        for i, v in requirements:
            req[i] = v
        
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0 and j == 0: return 1

            r = req[i-1] # 表示 perm[0]~perm[i-1] 中的逆序对的数量
            # 有逆序对约束
            if r != -1:
                return dfs(i-1, r) if r <= j <=r+i else 0

            return sum(dfs(i-1, j-k) for k in range(min(i,j)+1)) % MOD

        return dfs(n-1, req[-1])

if __name__ == "__main__":
    sol = Solution()
    n, requirements = 3, [[2,2],[0,0]]
    print(sol.numberOfPermutations(n, requirements))