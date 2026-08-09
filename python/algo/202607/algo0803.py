import copy
from typing import List

# 常用数据结构 - 7.2 并查集 - 进阶
class UnionFind:
    def __init__(self, n:int):
        self.fa = list(range(n))
        self.cc = [1] * n
    
    def find(self, x: int) -> int:
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]

    def merge(self, u: int, v:int) -> None:
        x, y = self.find(u), self.find(v)
        if x != y:
            self.fa[x] = y
            self.cc[y] += self.cc[x]
    
    def count(self, u:int) -> int:
        x = self.find(u)
        return self.cc[x]

class Solution:
    def hitBricks(self, grid: List[List[int]], hits: List[List[int]]) -> List[int]:
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        m, n = len(grid), len(grid[0])
        uf = UnionFind(m * n)

        last = copy.deepcopy(grid)
        for h in hits:
            last[h[0]][h[1]] = 0
        
        for i, row in enumerate(last):
            for j, v in enumerate(row):
                if v == 1:
                    if j+1 < n and last[i][j+1] == 1:
                        uf.merge(i*n+j, i*n+j+1)
                    if i+1 < m and last[i+1][j] == 1:
                        uf.merge(i*n+j, (i+1)*n+j)
        
        first = -1
        for j in range(n):
            if last[0][j] == 1:
                first = j
                break
        if first != -1:
            for j in range(first+1, n):
                if last[0][j] == 1:
                    uf.merge(first, j)
        
        prev = 0
        if first != -1:
            prev = uf.count(first)

        ans = []
        k = len(hits)
        for i in range(k-1, -1, -1):
            x, y = hits[i][0], hits[i][1]
            if grid[x][y] == 1:
                last[x][y] = 1
                if x == 0:
                    if first == -1: first = y
                    else: uf.merge(first, y)

                for dx, dy in dirs:
                    if 0 <= x + dx < m and 0 <= y + dy < n and last[x+dx][y+dy]:
                        uf.merge(x*n+y, (x+dx)*n + y + dy)
            cur = 0
            if first != -1:
                cur = uf.count(first)
                ans.append(max(0, cur - prev - 1))
                prev = cur
            else:
                ans.append(0)

        return ans[::-1]



if __name__ == "__main__":
    print(Solution().hitBricks([[1,0,0,0],[1,1,1,0]], [[1,0]]))