# 埃氏筛 求 质数
import heapq
from math import inf, isqrt
from typing import List

# 求质数
MX = 10 ** 4
is_prime = [True] * MX
is_prime[0] = is_prime[1] = False
for i in range(2, isqrt(MX) + 1):
    if is_prime[i]:
        for j in range(i * i, MX, i):
            is_prime[j] = False


class Solution:
    def minOperations(self, n: int, m: int) -> int:
        # 自行解答，使用 Dijkstra，比赛的时候没有想到
        LIMIT = 10 ** (len(str(n)))

        if is_prime[n] or is_prime[m]: return -1

        dis = [inf] * LIMIT
        vis = [False] * LIMIT
        dis[n] = n
        pq = [(0, n)]

        def adjacent(u:int) -> List[int]:
            ret = []
            us = str(u)
            for i in range(len(us)):
                for inc in (-1, 1):
                    if not 0<=inc+int(us[i])<=9: continue
                    v = u + inc * 10 ** (len(us)-i-1)
                    if not is_prime[v]: ret.append(v)
            return ret

        while pq:
            _, u = heapq.heappop(pq)
            if vis[u]: continue
            if u == m:break # 翦枝

            vis[u] = True
            for v in adjacent(u):
                if not vis[v] and dis[v] > dis[u]+v:
                    dis[v] = dis[u]+v
                    heapq.heappush(pq, (dis[v], v))

        return -1 if dis[m] == inf else dis[m]

if __name__ == "__main__":
    sol = Solution()
    print(sol.minOperations(10, 12))