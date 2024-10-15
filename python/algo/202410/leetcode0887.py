from functools import cache
from itertools import count


class Solution:
    def superEggDrop(self, k: int, n: int) -> int:
        @cache
        def dfs(cnt:int, e:int) -> int:
            if cnt == 0: return 0
            if e == 1: return cnt
            
            lo, hi = 1, cnt
            # keep a gap of 2 x values to manually check later
            while lo + 1 < hi:
                x = (lo + hi) // 2
                t1 = dfs(x-1, e-1)
                t2 = dfs(cnt-x, e)

                if t1 < t2:
                    lo = x
                elif t1 > t2:
                    hi = x
                else:
                    lo = hi = x

            return 1 + min(max(dfs(x-1, e-1), dfs(cnt-x, e)) for x in (lo, hi))
        
        return dfs(n, k)

    def superEggDrop2(self, k: int, n: int) -> int:
        @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        def dfs(i: int, j: int) -> int:
            if i == 0 or j == 0:
                return 0
            return dfs(i - 1, j) + dfs(i - 1, j - 1) + 1
     
        for i in count(1):
            if dfs(i, k) >= n:
                return i



if __name__ == "__main__":
    sol = Solution()
    print(sol.superEggDrop(3, 14))
    print(sol.superEggDrop2(3, 14))