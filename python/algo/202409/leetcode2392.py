from collections import defaultdict
from typing import List

# 周赛 308
class Solution:
    def buildMatrix(self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]) -> List[List[int]]:
        # key is [0..k-1], value is [r,c] in result
        # 自行解答，使用 拓扑排序
        pos = defaultdict(lambda:[-1,-1])

        def topsort(conditions: List[List[int]], rc:int)->bool:
            deg = [0] * k
            tops = set([i for i in range(k)])
            g = [[] for _ in range(k)]
            for u, v in conditions:
                if v - 1 in g[u-1]:continue
                g[u-1].append(v-1)
                deg[v-1] += 1
                if deg[u-1] == 0:
                    tops.add(u-1)
                tops -= set([v-1])

            inx = 0
            while inx < k:
                if len(tops) == 0:return False
                u = tops.pop()
                pos[u][rc] = inx
                for v in g[u]:
                    deg[v] -= 1
                    if deg[v] == 0:tops.add(v)
                inx += 1

            return True

        if not topsort(rowConditions,0):return []
        if not topsort(colConditions,1):return []
        
        result = [[0] * k for _ in range(k)]
        for k, [r,c] in pos.items():
            result[r][c] = k+1

        return result
if __name__ == "__main__":
    sol = Solution()
    k, rowConditions, colConditions = 3, [[1,2],[3,2]], [[2,1],[3,2]]
    k, rowConditions, colConditions = 8, [[1,2],[7,3],[4,3],[5,8],[7,8],[8,2],[5,8],[3,2],[1,3],[7,6],[4,3],[7,4],[4,8],[7,3],[7,5]], [[5,7],[2,7],[4,3],[6,7],[4,3],[2,3],[6,2]]
    print(sol.buildMatrix(k, rowConditions, colConditions))
        
        
