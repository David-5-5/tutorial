from typing import List

# 周赛 320
class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        # 除跟节点外，其他节点的子结点个数(包括自身) // seats 的上取整，即是这个节点到根节点的油耗
        g = [[] for _ in range(len(roads)+1)]
        for u, v in roads:
            g[u].append(v)
            g[v].append(u)
        
        ans = 0
        
        def dfs(u:int,fa:int) :
            nonlocal ans
            size = 1
            for v in g[u]:
                if v == fa:continue
                size += dfs(v, u)
            if u:
                ans += (size + seats - 1) // seats # ceil(size//seats)
            return size
        dfs(0, -1)
        return ans

if __name__ == "__main__":
    sol = Solution()
    roads, seats = [[0,1],[0,2],[0,3]], 5
    print(sol.minimumFuelCost(roads, seats))