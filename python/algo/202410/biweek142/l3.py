from functools import cache
from typing import List


class Solution:
    def maxScore(self, n: int, k: int, stayScore: List[List[int]], travelScore: List[List[int]]) -> int:
        
        @cache
        def dfs(i:int, j:int) -> int:
            if i == k: return 0
            res = 0
            for next in range(n):
                if next == j:
                    res = max(res, dfs(i+1, next) + stayScore[i][j])
                else:
                    res = max(res, dfs(i+1, next) + travelScore[j][next])
            return res

        return max(dfs(0, j) for j in range(n))


if __name__ == "__main__":
    sol = Solution()
    n , k, stayScore, travelScore = 2, 1, [[2,3]], [[0,2],[1,0]]
    n , k, stayScore, travelScore = 3, 2, [[3,4,2],[2,1,2]], [[0,2,1],[2,0,4],[3,2,0]]
    print(sol.maxScore(n , k, stayScore, travelScore))