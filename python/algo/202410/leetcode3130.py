from functools import cache
from math import perm

# 双周赛 129
class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:
        # 参考题解，记忆化搜索减少一维
        MOD = 1_000_000_007

        @cache
        def dfs(cnt0:int, cnt1:int, cur:int) -> int:
            # 状态转移方程:
            # f(c0, c1, 0) = f(c0-1,c1,0) + f(c0-1,c1,1) - f(c0-limit-1, c1, 1)
            # f(c0, c1, 1) = f(c0,c1-1,0) + f(c0,c1-1,1) - f(c0,c1-limit-1, 0)
            # 参数说明:
            # cnt0 使用 0 的数量
            # cnt1 使用 1 的数量
            # 第 cnt0 + cnt1 位 填写 cur , where cur ∈ {0,1}
            # 边界情况:
            # 如果 cnt0 为 0，那么当 cur 为 1 或者 cnt1 大于 limit 时，不存在这样的稳定数组，返回 0，否则返回 1。
            if cnt0 == 0:
                return 1 if cur == 1 and cnt1 <= limit else 0
            if cnt1 == 0:
                return 1 if cur == 0 and cnt0 <= limit else 0

            # res = 0
            # if cur == 0: res += dfs(cnt0-1,cnt1,0) + dfs(cnt0-1,cnt1,1)
            # if cur == 0 and cnt0 > limit: res -= dfs(cnt0-limit-1, cnt1, 1)

            # if cur == 1: res += dfs(cnt0,cnt1-1,0) + dfs(cnt0,cnt1-1,1)
            # if cur == 1 and cnt1 > limit: res -= dfs(cnt0, cnt1-limit-1, 0)
            # return res% MOD
            
            if cur == 0: 
                return (dfs(cnt0-1,cnt1,0) + dfs(cnt0-1,cnt1,1)-(dfs(cnt0-limit-1, cnt1, 1) if cnt0>limit else 0)) % MOD
            else:
                return (dfs(cnt0,cnt1-1,0) + dfs(cnt0,cnt1-1,1)-(dfs(cnt0, cnt1-limit-1, 0) if cnt1>limit else 0)) % MOD
        
        ans = (dfs(zero, one, 0) + dfs(zero, one, 1)) % MOD
        dfs.cache_clear()
        return ans

    def numberOfStableArrays_OOM(self, zero: int, one: int, limit: int) -> int:
        # 自行解答，记忆化搜索, 超出内存限制
        MOD = 1_000_000_007
        @cache
        def dfs(cnt0:int, cnt1:int, prev:int, cnt:int) -> int:
            if cnt0 == zero and cnt1 == one:
                return 1

            res = 0
            if cnt0 < zero and prev != 0:
                res += dfs(cnt0+1, cnt1, 0, 1)
            if cnt0 < zero and prev == 0 and cnt < limit:
                res += dfs(cnt0+1, cnt1, 0, cnt+1)
            if cnt1 < one and prev != 1:
                res += dfs(cnt0, cnt1+1, 1, 1)
            if cnt1 < one and prev == 1 and cnt < limit:
                res += dfs(cnt0, cnt1+1, 1, cnt+1)
            return res % MOD

        return dfs(0,0,-1,0)


if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOfStableArrays(1,3,3))