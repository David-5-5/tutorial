from collections import defaultdict
from typing import List

class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        g = defaultdict(set)
        for u, v in edges:
            g[u].add(v)
            g[v].add(u)
        
        odd = []
        for u in g.keys():
            if len(g[u]) % 2 == 1:
                odd.append(u)
        
        if len(odd) % 2 == 1 or len(odd) > 4:return False
        if len(odd) == 0:return True

        if len(odd) == 2:
            u, v = odd
            if u not in g[v]: return True # u, v之间不存在边
            for i in range(1, n+1): # 找一个u, v不存在边的节点
                if i not in g[v] and i not in g[u]:return True

        if len(odd) == 4:
            # 其中三个节点之间不存在环
            a, b, c, d = odd
            # 下式表示： a - b, c - d 之间连线 or a - c, b - d 之间连线 or a - d, b - c 之间连线
            # 两两连线的要求 之前不存在边
            return b not in g[a] and d not in g[c] or \
                   c not in g[a] and d not in g[b] or \
                   d not in g[a] and c not in g[b]
            
        return False


if __name__ == "__main__":
    sol = Solution()
    n, edges = 11, [[5,9],[8,1],[2,3],[7,10],[3,6],[6,7],[7,8],[5,1],[5,7],[10,11],[3,7],[6,11],[8,11],[3,4],[8,9],[9,1],[2,10],[9,11],[5,11],[2,5],[8,10],[2,7],[4,1],[3,10],[6,1],[4,9],[4,6],[4,5],[2,4],[2,11],[5,8],[6,9],[4,10],[3,11],[4,7],[3,5],[7,1],[2,9],[6,10],[10,1],[5,6],[3,9],[2,6],[7,9],[4,11],[4,8],[6,8],[3,8],[9,10],[5,10],[2,8],[7,11]]
    print(sol.isPossible(n, edges))