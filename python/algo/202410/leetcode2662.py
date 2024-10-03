from cmath import inf
from collections import defaultdict
import heapq
from typing import List

# 周赛 343
class Solution:
    def minimumCost(self, start: List[int], target: List[int], specialRoads: List[List[int]]) -> int:
        def dis(x1:int, y1:int, x2:int, y2:int):
            return abs(x2-x1) + abs(y2-y1)
        
        sx, sy = start
        tx, ty = target
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
        vis = {key:False for key in g.keys()}
        path = {key:inf for key in g.keys()}
        path[(sx,sy)] = 0
        vis[(tx, ty)] = False
        path[(tx, ty)] = inf
        # vis[(sx,sy)] = True
        # for x, y, c in g[(sx, sy)]:
        #     pg.append(c, x, y)
        # heapq.heapify(pg)
        while pg:
            _, x, y = heapq.heappop(pg)
            if vis[(x,y)]:continue
            if (x,y) == (tx,ty): return path[(tx,ty)]
            vis[(x,y)] = True
            for u, v, c in g[(x,y)]:
                heapq.heappush(pg, (c, u, v))
                path[(u,v)] = min(path[(u,v)], path[(x,y)]+c)
    
if __name__ == "__main__":
    sol = Solution()
    start, target, specialRoads = [1,1], [4,5], [[1,2,3,3,2],[3,4,4,5,1]]
    start, target, specialRoads = [1,1], [10,4], [[4,2,1,1,3],[1,2,7,4,4],[10,3,6,1,2],[6,1,1,2,3]]
    print(sol.minimumCost(start, target, specialRoads))