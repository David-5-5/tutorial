from cmath import inf
from collections import defaultdict
import heapq
from typing import List

# 周赛 343
class Solution:
    def minimumCost(self, start: List[int], target: List[int], specialRoads: List[List[int]]) -> int:
        # 自行解答，牢牢记清楚公式
        def dis(x1:int, y1:int, x2:int, y2:int):
            return abs(x2-x1) + abs(y2-y1)
        
        sx, sy = start
        tx, ty = target
        if (sx, sy) == (tx,ty): return 0
        g = defaultdict(list)
        g[(sx, sy)].append((tx, ty, dis(sx, sy, tx, ty)))

        for x1, y1, x2, y2, c in specialRoads:
            g[(x1,y1)].append((x2, y2, c))
            g[(sx, sy)].append((x1,y1,dis(sx,sy,x1,y1)))
            g[(x2,y2)].append((tx,ty, dis(x2,y2,tx,ty)))
        
        ns = len(specialRoads)
        sr = specialRoads
        for i in range(ns-1):
            for j in range(i, ns):
                g[(sr[i][2],sr[i][3])].append((sr[j][0],sr[j][1], dis(sr[i][2],sr[i][3],sr[j][0],sr[j][1])))
                g[(sr[j][2],sr[j][3])].append((sr[i][0],sr[i][1], dis(sr[j][2],sr[j][3], sr[i][0],sr[i][1])))

        pg = [(0, sx, sy)]
        vis = []
        path = {key:inf for key in g.keys()}
        path[(sx,sy)] = 0
        path[(tx, ty)] = inf

        while pg:
            _, x, y = heapq.heappop(pg)
            if (x, y) in vis: continue
            vis.append((x,y))
            for u, v, c in g[(x,y)]:
                if path[(u,v)] > path[(x,y)]+c:
                    path[(u,v)] = path[(x,y)]+c
                    heapq.heappush(pg, (path[(u,v)], u, v))
        return  path[(tx,ty)]
    
if __name__ == "__main__":
    sol = Solution()
    start, target, specialRoads = [1,1], [4,5], [[1,2,3,3,2],[3,4,4,5,1]]
    start, target, specialRoads = [1,1], [4,9], [[3,2,4,5,2],[4,5,4,1,1],[1,9,2,9,2],[2,2,2,5,3]]
    print(sol.minimumCost(start, target, specialRoads))