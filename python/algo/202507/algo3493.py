from typing import List

# 常用数据结构 - 7.1 并查集 - 基础

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
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        sets = list(map(set, properties))
        uf = UnionFind(len(properties))
        for i, a in enumerate(sets):
            for j, b in enumerate(sets[:i]):
                if len(a & b) >= k: uf.merge(j, i)

        return uf.cc