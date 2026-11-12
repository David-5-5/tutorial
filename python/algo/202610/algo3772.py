from typing import List


class Solution:
    def maxSubgraphScore(self, n: int, edges: List[List[int]], good: List[int]) -> List[int]:
        # 自行解答，换根 DP
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        ans = [-n] * n

        def dfs(u: int, fa: int) -> int:
            res = 0
            for v in g[u]:
                if v == fa: continue
                cld = dfs(v, u)
                if cld > 0: res += cld

            ans[u] = res + (1 if good[u] == 1 else -1)
            return ans[u]
        dfs(0, -1)

        def reroot(u: int, fa: int) :
            for v in g[u]:
                if v == fa: continue
                if ans[u] - max(0, ans[v]) > 0:
                    ans[v] += ans[u] - max(0, ans[v])
                reroot(v, u)
        
        reroot(0, -1)
        return ans

if __name__ == "__main__":
    print(Solution().maxSubgraphScore(3, [[0,1],[1,2]], [1,0,1]))