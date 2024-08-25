from typing import List

# 双周赛 114
class Solution:
    def maxKDivisibleComponents(self, n: int, edges: List[List[int]], values: List[int], k: int) -> int:
        # 参考题解
        g = [[] for _ in range(n)]

        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        ans = 0

        def dfs(u:int, fa:int) -> int:
            nonlocal ans
            res = values[u]
            for v in g[u]:
                if v == fa: continue
                res += dfs(v, u)

            if res % k == 0:ans += 1
            return res % k

        dfs(0,-1)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    n, edges, values, k = 5, [[0,2],[1,2],[1,3],[2,4]], [1,8,1,4,4], 6
    print(sol.maxKDivisibleComponents( n, edges, values, k))
    