import heapq
from typing import List

# 类似于 3362 maxRemoval
class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        # 贪婪 + 大顶堆，比 3362 简单，不需要差分数组
        stations.sort() # 以 posi 排序
        n, ans, dis, j, h = len(stations), 0, startFuel, 0, []

        while dis < target:
            while j < n and stations[j][0] <= dis: # 将能够行驶范围内的油加入堆中 
                heapq.heappush(h, -stations[j][1])
                j += 1
            
            if h: 
                dis -= heapq.heappop(h) # 每次从堆中取最大的油
                ans += 1                # 加油次数 +1
            else: return -1             # 无法加油，无法到达目的地
        return ans  

if __name__ == "__main__":
    sol = Solution()
    target, startFuel, stations = 100, 10, [[10,60],[20,30],[30,30],[60,40]]
    print(sol.minRefuelStops(target, startFuel, stations))