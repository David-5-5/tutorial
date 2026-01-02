from typing import List

# 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution:
    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        # 自行解答 基础
        n = len(rooms)
        vis = [False] * n

        def dfs(u: int) :
            for v in rooms[u]:
                if vis[v]: continue
                vis[v] = True
                dfs(v)
        
        vis[0] = True
        dfs(0)
        return all(vis)