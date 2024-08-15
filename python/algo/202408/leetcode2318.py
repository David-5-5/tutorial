from functools import cache

# 双周赛 81 自行解答，记忆化搜索

MOD = 10 ** 9 + 7
g = [[] for _ in range(7)]
g[0] = set([1,2,3,4,5,6])
g[1] = set([2,3,4,5,6])
g[2] = set([1,3,5])
g[3] = set([1,2,4,5])
g[4] = set([1,3,5])
g[5] = set([1,2,3,4,6])
g[6] = set([1,5])

class Solution:
    def distinctSequences(self, n: int) -> int:

        @cache
        def dfs(i:int,p1:int, p2:int) -> int:
            if i == n: return 1

            res = 0

            for next in g[p2]:
                if next == p1:continue
                res += dfs(i+1, p2, next)

            return res % MOD
        return dfs(0, 0, 0)

if __name__ == "__main__":
    sol = Solution()
    print(sol.distinctSequences(222))
