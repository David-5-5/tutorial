from math import inf
from typing import List

# 双周赛 119
class Solution:
    def numberOfSets(self, n: int, maxDistance: int, roads: List[List[int]]) -> int:
        # 参考题解 Floyd 最短路径算法 结合 位集合运算
        def check(bs:int) -> int:
            # 初始化 i == j 表示 节点相同，即节点到自身的距离， bs>>i==0 表示节点 i 不在集合中
            f = [[0 if i==j or bs>>j&1==0 or bs>>i&1==0 else inf for i in range(n)] for j in range(n)]

            for u, v, w in roads:
                if f[u][v] > w:
                    f[u][v] = w
                    f[v][u] = w

            for k in range(n):
                if bs>>k & 1 == 0: continue
                for x in range(n):
                    if bs>>x & 1 == 0 or f[x][k] == inf: continue
                    for y in range(n):
                        if bs>>y & 1 == 0  or f[y][k] == inf: continue
                        f[x][y] = min(f[x][y], f[x][k] + f[k][y])

            return 1 if max(max(row) for row in f) <= maxDistance else 0
        
        return sum(check(s) for s in range(1<<n))


    def numberOfSets2(self, n: int, maxDistance: int, roads: List[List[int]]) -> int:
        # 优化性能 将 f 的初始化在 check 外
        fg = [[0 if i==j else inf for i in range(n)] for j in range(n)]

        for u, v, w in roads:
            if fg[u][v] > w:
                fg[u][v] = w
                fg[v][u] = w
        
        def check(bs:int) -> int:
            f = [row.copy() for row in fg] # 二维数组复制 f = fg.copy() is WRONG

            for k in range(n):
                if bs>>k & 1 == 0: continue
                for x in range(n):
                    if bs>>x & 1 == 0 or f[x][k] == inf: continue
                    for y in range(n):
                        if bs>>y & 1 == 0  or f[y][k] == inf: continue
                        f[x][y] = min(f[x][y], f[x][k] + f[k][y])

            for x in range(n):
                if bs>>x & 1 == 0: continue
                for y in range(n):
                    if bs>>y & 1 == 0: continue
                    if f[x][y] > maxDistance: return 0

            return 1

        return sum(check(s) for s in range(1<<n))
    

if __name__ == "__main__":
    sol = Solution()
    n, maxDistance, roads = 3, 5, [[0,1,2],[1,2,10],[0,2,10]]
    n, maxDistance, roads = 5, 25, [[1,0,17],[1,0,1],[2,1,24],[3,2,12],[1,0,7],[3,2,4],[2,1,15],[0,4,14]]
    print(sol.numberOfSets(n, maxDistance, roads))
    print(sol.numberOfSets2(n, maxDistance, roads))