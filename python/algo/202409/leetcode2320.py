from functools import cache

# 周赛 299 
class Solution:
    def countHousePlacements(self, n: int) -> int:
        # 自行解答 记忆化搜索 选或不选
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, prev:bool)->int:
            if i == n:return 1

            res = dfs(i+1, False) # 不选
            if prev == False: res += dfs(i+1, True) # 选

            return res % MOD
        
        res = dfs(0, False)
        return  res * res % MOD

if __name__ == "__main__":
    sol = Solution()
    print(sol.countHousePlacements(100))