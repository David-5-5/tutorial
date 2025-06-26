from cmath import inf
from functools import cache
from heapq import heappop, heappush


class Solution:
    def racecar(self, target: int) -> int:
        # 自行解答 广度优先搜索 + 优先队列
        n = step = 1 
        while n <= target: n <<= 1

        dp = [inf] * n
        dp[0] = 0
        q = []
        while (1 << step) - 1 < n:
            heappush(q, (step, (1 << step)-1, 1))
            step += 1

        while q:
            val, pos, dir = heappop(q)
            if pos == target: return val
            if val > dp[pos]: continue
            else: dp[pos] = val
            # 反方向
            step = 1
            while 0 < pos + dir * -1 * ((1<<step) - 1) < n:
                nxtPos = pos + dir * -1 * ((1<<step) - 1)
                if dp[nxtPos] > val + step + 1:
                    heappush(q, (val + step + 1, nxtPos, dir*-1))
                step += 1
            # 同方向
            step = 1
            while 0 < pos + dir * ((1<<step) - 1) < n:
                nxtPos = pos + dir * ((1<<step) - 1)
                if dp[nxtPos] > val + step + 2:
                    heappush(q, (val + step + 2, nxtPos, dir))
                step += 1

        return -1


if __name__ == "__main__":
    sol = Solution()
    print(sol.racecar(3))