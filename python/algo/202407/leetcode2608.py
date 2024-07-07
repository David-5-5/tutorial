from collections import deque
from math import inf
from typing import List


class Solution:
    def findShortestCycle(self, n: int, edges: List[List[int]]) -> int:

        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def bfs(start:int) -> int:
            ans = inf
            dis = [-1] * n
            dis[start] = 0

            q = deque([(start, -1)])
            while q:
                u, fa = q.popleft()
                for v in graph[u]:
                    if dis[v] < 0:
                        dis[v] = dis[u] + 1
                        q.append((v, u))
                    elif v != fa:
                        ans = min(ans, dis[v] + dis[u] + 1)
            return ans
        ans = min(bfs(i) for i in range(n))
        return -1 if ans == inf else ans

if __name__ == "__main__":
    n = 6
    edges = [[4,2],[5,1],[5,0],[0,3],[5,2],[1,4],[1,3],[3,4]]
    solution = Solution()
    print(solution.findShortestCycle(n, edges))