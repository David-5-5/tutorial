from typing import List

# 常用数据结构 - 7.2 并查集 - 进阶
class UnionFind:
    def __init__(self, n:int):
        self.fa = list(range(n))
        self.cc = n                 # 连通块数目
    
    def find(self, x: int) -> int:
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]

    def merge(self, u: int, v:int) -> None:
        x, y = self.find(u), self.find(v)
        if x != y:
            self.fa[x] = y
            self.cc -= 1

class Solution:
    def latestDayToCross(self, row: int, col: int, cells: List[List[int]]) -> int:
        # 参考题解，时光倒流 - 使用并查集
        uf = UnionFind(row*col + 2)
        top, bottom = row * col, row * col + 1
        grid = [[0] * col for _ in range(row)]
        for i in range(len(cells)-1, -1, -1):   # 倒序遍历
            r, c = cells[i][0]-1, cells[i][1]-1
            grid[r][c] = 1
            for nr, nc in [(r-1,c),(r+1,c),(r,c-1),(r,c+1)]:
                if 0 <= nr < row and 0 <= nc < col and grid[nr][nc]:
                    uf.merge(r*col+c, nr*col+nc)
                if r == 0:  uf.merge(r*col + c, top)
                if r == row-1:  uf.merge(r*col + c, bottom)
            if uf.find(top) == uf.find(bottom): return i
