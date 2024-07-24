from heapq import nlargest
from typing import List

# 双周赛 93
class Solution:
    def maxStarSum(self, vals: List[int], edges: List[List[int]], k: int) -> int:
        g = [[] for _ in range(len(vals))]
        for e in edges:
            if vals[e[1]] > 0 : g[e[0]].append(vals[e[1]])
            if vals[e[0]] > 0 : g[e[1]].append(vals[e[0]])
        
        return max(sum(nlargest(k, e)) + vals[v] for v, e in enumerate(g))


if __name__ == "__main__":
    sol = Solution()
    vals, edges, k = [1,2,3,4,10,-10,-20], [[0,1],[1,2],[1,3],[3,4],[3,5],[3,6]], 2
    print(sol.maxStarSum(vals, edges, k))