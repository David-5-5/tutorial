from collections import defaultdict, deque
from typing import List

class Solution:
    def minEdgeReversals(self, n: int, edges: List[List[int]]) -> List[int]:
        
        graph = [[] for _ in range(n)] 

        for e in edges:
            graph[e[0]].append((e[1],1))
            graph[e[1]].append((e[0],-1))
        

        ans = [0] * n
        def dfs(i:int, fa:int) :
            for v, dir in graph[i]:
                if v != fa:
                    if dir < 0: ans[0]+=1
                    dfs(v,i)

        dfs(0, -1)
        
        def reroot(i:int, fa:int): 
            for v, dir in graph[i]:
                if v != fa:
                    ans[v] = ans[i] + dir
                    reroot(v, i)
                    
        reroot(0, -1)             

        return ans
if __name__ == "__main__":
    sol = Solution()
    n, edges = 4, [[0,3],[1,2],[2,3]]
    print(sol.minEdgeReversals(n, edges))

