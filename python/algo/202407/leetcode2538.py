from math import inf
from typing import List


class Solution:
    def maxOutput(self, n: int, edges: List[List[int]], price: List[int]) -> int:
        graph = [[] for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])


        ans = 0
        def dfs(u:int, fa:int) :
            nonlocal ans
            mf = mno  = 0
            for v in graph[u]:
                if v == fa: continue
                full, notail = dfs(v, u)
                if mf == 0:
                    ans = max(ans, full, notail + price[u])
                else:
                    ans = max(ans, full + mno + price[u], notail + mf + price[u])
                if full > mf : mf = full
                if notail > mno : mno = notail
            
            return mf + price[u], mno + (price[u] if mf else 0)
        dfs(0, -1)
        return ans
    

if __name__ == "__main__":
    solution = Solution()
    n, edges, price = 6, [[0,1],[1,2],[1,3],[3,4],[3,5]], [9,8,7,6,10,5]
    n, edges, price = 9, [[1,7],[5,2],[2,3],[6,0],[0,4],[4,7],[7,3],[3,8]], [6,13,8,10,4,5,8,3,12]
    print(solution.maxOutput(n, edges, price))