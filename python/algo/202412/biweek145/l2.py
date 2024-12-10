from cmath import inf
from functools import cache
from itertools import permutations
from typing import List


class Solution:
    def findMinimumTime(self, strength: List[int], K: int) -> int:
        # 自行解答，全排列 超过比赛时间了
        time = inf
        for nums in permutations(range(len(strength))):
            X = 1
            cur = 0
            for i in nums:
                mn = (strength[i]+X-1) // X # upper
                cur += mn
                X += K
            time = min(time, cur)
        return time


    def findMinimumTime2(self, strength: List[int], K: int) -> int:
        # 参考题解，全排列 + 剪枝
        n = len(strength)
        time = inf
        done = [False] * n
        def dfs(i:int, t:int) -> None:
            nonlocal time
            # if t>=time: return # 剪枝
            if i == n:
                if time > t: time = t        
            X = 1 + i * K
            for j, v in enumerate(strength):
                if not done[j]:
                    done[j] = True
                    dfs(i+1, t + (v-1)//X + 1)
                    done[j] = False

        dfs(0, 0)
        return time

    def findMinimumTime3(self, strength: List[int], K: int) -> int:
        # 参考题解，状压 DP
        n = len(strength)

        @cache
        def dfs(i:int) -> None:
            if i == 0:
                return 0
            X = 1 + K * (n-i.bit_count())
            res = inf
            for j in range(n):
                if i >> j & 1:
                    res = min(res, dfs(i-(1<<j)) + (strength[j]-1)//X + 1)
            return res
        
        return dfs((1 << n) - 1)

if __name__ == "__main__":
    sol = Solution()
    strength, K = [21,22,40,12,43,21], 3
    print(sol.findMinimumTime(strength, K))
    print(sol.findMinimumTime3(strength, K))