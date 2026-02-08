from cmath import inf
import heapq
from itertools import combinations
from math import floor
from typing import List

#  图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        # 自行解答 2602
        # dis[d][s][m]  
        # d 表示河的两岸，0：出发 1 目的
        # s 表示压缩状态，包含的人
        # m 表示周期数
        dis = [[[inf] * m for _ in range(1<<n)] for _ in range(2)]
        tot = (1 << n) - 1
        def comb_mx(state: int, bits: int) -> List[List[int]]:
            if state.bit_count() <= bits:
                mx_time = 0
                for b in range(n):
                    if state >> b & 1:
                        mx_time = max(mx_time, time[b])
                return [[state, mx_time]]

            arr = []
            for bit in range(n):
                if state >> bit & 1:
                    arr.append(bit)
            
            ans, mx_time = [], 0
            for c in combinations(arr, bits):
                val, mx_time = 0, 0
                for bit in c:
                    val |= 1 << bit 
                    mx_time = max(mx_time, time[bit])
                ans.append([val, mx_time])
            return ans

        pq = []
        dis[0][tot][0] = 0
        heapq.heappush(pq, (0.0, 0, tot, 0))
        while pq:
            t, d, s, curm = heapq.heappop(pq)
            if t > dis[d][s][curm]: continue
            
            if d == 0:
                for sub, mx in comb_mx(s, k):
                    op_s = tot + sub - s
                    op_t = t + mx * mul[curm]
                    op_m = (floor(mx * mul[curm]) + curm) % m
                    if (op_t < dis[1][op_s][op_m]):
                        dis[1][op_s][op_m] = op_t
                        if (op_s < tot):
                            heapq.heappush(pq, (op_t, 1, op_s, op_m))
            else:
                for sub, mx in comb_mx(s, 1):
                    op_s = tot - s + sub
                    op_t = t + mx * mul[curm]
                    op_m = (floor(mx * mul[curm]) + curm) % m

                    if (op_t < dis[0][op_s][op_m]):
                        dis[0][op_s][op_m] = op_t
                        heapq.heappush(pq, (op_t, 0, op_s, op_m))

        ans = min(dis[1][-1])
        return ans if ans < inf else -1 

if __name__ == "__main__":
    n = 3
    k = 2
    m = 3
    time = [2,5,8]
    mul = [1.0,1.5,0.75]
    print(Solution().minTime(n, k, m, time, mul))