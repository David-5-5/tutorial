from functools import cache


class Solution:
    def countKReducibleNumbers(self, s: str, k: int) -> int:
        # 参考题解
        MOD = 1_000_000_007
        n = len(s)

        # 数位 DP
        @cache
        def dfs(i:int, left:int, is_limit:bool) -> int:
            if i == n:
                return 0 if is_limit or left else 1
            
            res = 0
            up = int(s[i]) if is_limit else 1
            for d in range(min(up,left) + 1): # 剪枝，当left == 0时,后续全取 0
                res += dfs(i + 1, left-d, is_limit and d == up)
            return res % MOD

        ans = 0
        f = [0] * n
        for i in range(1, n):
            f[i] = f[i.bit_count()] + 1 if i > 1 else 0
            if f[i] < k:
                ans = (ans + dfs(0, i, True)) % MOD
        dfs.cache_clear()
        return ans
        
if __name__ == "__main__":
    sol = Solution()
    s, k = "111", 1
    print(sol.countKReducibleNumbers(s, k))
