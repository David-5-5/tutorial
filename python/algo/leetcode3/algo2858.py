from collections import defaultdict, deque
from typing import List

class Solution:
    def minEdgeReversals(self, n: int, edges: List[List[int]]) -> List[int]:
        
        children = set()
        graph = defaultdict(list)

        for e in edges:
            graph[e[0]].append(e[1])
            children.add(e[1])
        
        root = list(set([i for i in range(n)]) - children)

        ans = [0] * n
        
        que = deque()
        que.append((root[0], 0))
        while que:
            i, l = que.popleft()
            ans[i] = l
            for v in graph[i]:
                que.append((v, l+1))
        return ans
if __name__ == "__main__":
    sol = Solution()
    n, edges = 4, [[0,3],[1,2],[2,3]]
    print(sol.minEdgeReversals(n, edges))

