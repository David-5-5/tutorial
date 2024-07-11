from collections import defaultdict
from typing import List

class Solution:
    def rootCount(self, edges: List[List[int]], guesses: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        h = {}
        for u, v in guesses:
            h[(u,v)] = False
        
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        ans = res = 0
        def dfs(u:int, fa:int):
            nonlocal res
            for v in g[u]:
                if v == fa : continue
                if (u,v) in h.keys():
                    h[(u,v)] = True
                    res += 1
                dfs(v, u)
        dfs(0, -1)
        ans += (res>=k)

        def reroot(u:int, res, fa:int):
            nonlocal ans
           
            for v in g[u]:
                newres = res
                if v == fa : continue
                if (u,v) in h.keys():
                    h[(u,v)] = False
                    newres -= 1
                if (v,u) in h.keys():
                    h[(v,u)] = True
                    newres += 1
                ans += (newres >= k)
                reroot(v, newres, u)
        reroot(0, res, -1)
        return ans

if __name__ == "__main__":
    sol = Solution()
    edges, guesses, k = [[0,1],[1,2],[1,3],[4,2]], [[1,3],[0,1],[1,0],[2,4]], 3
    edges, guesses, k = [[0,1],[1,2],[2,3],[3,4]], [[1,0],[3,4],[2,1],[3,2]], 1

    print(sol.rootCount(edges, guesses, k))