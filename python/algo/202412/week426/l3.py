from bisect import bisect_left
from itertools import accumulate
from typing import List


class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]], k: int) -> List[int]:
        n, m = len(edges1) + 1, len(edges2) + 1
        g1, g2 = [[] for _ in range(n)], [[] for _ in range(m)]
        for u, v in edges1:
            g1[u].append(v)
            g1[v].append(u)

        for u, v in edges2:
            g2[u].append(v)
            g2[v].append(u)

    
if __name__ == "__main__":
    sol = Solution()
    nums, queries = [10], [[0,0,5],[0,0,3],[0,0,2],[0,0,1],[0,0,4],[0,0,1],[0,0,4],[0,0,5],[0,0,3],[0,0,4],[0,0,1]]
    print(sol.isZeroArray(nums,queries))