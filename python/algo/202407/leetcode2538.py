from math import inf
from typing import List

# 周赛328 
class Solution:
    def maxOutput(self, n: int, edges: List[List[int]], price: List[int]) -> int:
        graph = [[] for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])


        ans = 0
        # def dfs(u:int, fa:int) :
        #     nonlocal ans
        #     mx_f = mx_h  = 0
        #     for v in graph[u]:
        #         if v == fa: continue
        #         f, h = dfs(v, u) # f, 带叶子节点的最大输出，不包含叶子节点的最大输出
        #         if mx_f == 0:
        #             ans = max(ans, f, h + price[u]) # 第一个节点 f不包含当前节点
        #         else:
        #             ans = max(ans, f + mx_h + price[u], h + mx_f + price[u])
        #         if f > mx_f : mx_f = f
        #         if h > mx_h : mx_h = h
            
        #     return mx_f + price[u], mx_h + (price[u] if mx_f else 0)

        # 另一种写法
        def dfs(u:int, fa:int) :
            nonlocal ans
            mx_f = p = price[u]
            mx_h  = 0
            for v in graph[u]:
                if v == fa: continue
                f, h = dfs(v, u)
                ans = max(ans, f + mx_h, h + mx_f)
                if f + p > mx_f : mx_f = f+p
                if h + p > mx_h : mx_h = h+p
            
            return mx_f, mx_h

        dfs(0, -1)
        return ans
    

if __name__ == "__main__":
    solution = Solution()
    n, edges, price = 6, [[0,1],[1,2],[1,3],[3,4],[3,5]], [9,8,7,6,10,5]
    n, edges, price = 9, [[1,7],[5,2],[2,3],[6,0],[0,4],[4,7],[7,3],[3,8]], [6,13,8,10,4,5,8,3,12]
    print(solution.maxOutput(n, edges, price))