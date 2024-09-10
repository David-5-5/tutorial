from collections import defaultdict
from typing import List
from sortedcontainers import SortedDict

# 周赛 304
class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        # 自行解答，超时
        n = len(edges)
        
        qs = SortedDict()
        for i in range(n):qs[i] = -1
        
        res = -1
        def dfs(u:int, l:int) :
            if u not in qs.keys() : return
            nonlocal res
            qs[u] = l
            v = edges[u]
            if v != -1 and v in qs.keys() and qs[v]==-1:
                dfs(v, l+1)
            elif v != -1 and v in qs.keys():
                res = max(res, l - qs[v] + 1)
            
            del qs[u]
        
        while qs: # 未划分连通图，每个节点遍历的代价太高了
            dfs(min(qs), 0)
        return res

    def longestCycle2(self, edges: List[int]) -> int:
        # 自行解答，使用并查集划分连通子图，然后从每个连通子图任意一点出发，查找是否存在环
        # 由于每个顶点仅有一个出边，因此存在环的子图从任意一点出发都可以找到环
        n = len(edges)
        fa = [i for i in range(n)] # 并查集
        # fa = list(range(n+1))
        def find(x:int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]
        
        for u, v in enumerate(edges):
            if v == -1: continue
            fu = find(u)
            fv = find(v)
            if fu != fv:
                fa[fv] = fu
        
        subs = set()
        for i in range(n):
            j = find(i)
            if j not in subs:subs.add(j)

        res = -1
        
        def checkcycle(u:int, l):
            nonlocal res
            if u == -1:return
            if u in level.keys():
                res = max(res, l-level[u])
                return
            level[u] = l
            checkcycle(edges[u],l+1)

        for u in subs:
            level = {}
            checkcycle(u, 0)
            # l = 0
            # while u != -1:
            #     if u in level.keys(): # cycle
            #         res = max(res, l - level[u])
            #         break
            #     else:
            #         level[u] = l
            #     l += 1
            #     u = edges[u]
        
        return res
    

if __name__ == "__main__":
    sol = Solution()
    edges = [3,3,4,2,3]
    edges = [3,4,0,2,-1,2]
    print(sol.longestCycle(edges))
    print(sol.longestCycle2(edges))