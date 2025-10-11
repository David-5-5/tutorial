from typing import List

# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def countPairs(self, n: int, edges: List[List[int]]) -> int:
        # 自行解答 
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        prev, ans = 0, 0
        vis = set()
        # BEGIN dfs 求连通图 
        def dfs(u : int):
            vis.add(u)
            for v in g[u]:
                if v not in vis: dfs(v)
        for i in range(n):
            if i not in vis:
                dfs(i)
                ans += (len(vis) - prev) * (n-len(vis)+prev)
                # 下面写法不需要除以 2，歪打正着
                # ans += (len(vis) - prev) * (n-len(vis))   
                prev = len(vis)
        # END dfs 求连通图 

        # return ans # 自己的思路是求组合数之后需要 减半除以2, 结果尽然不需要了???
        return ans // 2


if __name__ == "__main__":
    sol = Solution()
    print(sol.countPairs(12, []))


