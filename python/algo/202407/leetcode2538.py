from math import inf
from typing import List


class Solution:
    def maxOutput(self, n: int, edges: List[List[int]], price: List[int]) -> int:
        graph = [[] for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])

        dp = [0] * n
        ans = 0
        # def dfs(u:int, fa:int):
        #     nonlocal ans
        #     for v in graph[u]:
        #         if v == fa:continue
        #         dfs(v, u)
        #         ans = max(ans, dp[u] + dp[v] + price[v])
        #         dp[u] = max(dp[u], dp[v] + price[v])
        # dfs(3, -1)

        def dfs(u:int, fa:int):
            nonlocal ans
            for v in graph[u]:
                if v == fa:continue
                dp[v] = dp[u] + price[v]
                if dp[v] > dp[ans] : ans = v
                dfs(v, u)
        dp[0] = price[0]
        dfs(0, -1)
        ans1 = ans
        dp[ans] = price[ans]
        dfs(ans, -1)

        minp = price[ans]
        def dfsm(u:int, fa:int) -> bool:
            nonlocal minp
            if u == ans1:
                return True
            for v in graph[u]:
                if v == fa: continue
                if dfsm(v, u):
                    if minp > price[v]:
                        minp = price[v]
                    return True
            return False

        dfsm(ans, -1)
        return dp[ans] - minp
    

if __name__ == "__main__":
    solution = Solution()
    n, edges, price = 6, [[0,1],[1,2],[1,3],[3,4],[3,5]], [9,8,7,6,10,5]
    n, edges, price = 9, [[1,7],[5,2],[2,3],[6,0],[0,4],[4,7],[7,3],[3,8]], [6,13,8,10,4,5,8,3,12]
    print(solution.maxOutput(n, edges, price))