from typing import List


class Solution:
    def pathWithObstacles(self, obstacleGrid: List[List[int]]) -> List[List[int]]:
        m, n = len(obstacleGrid), len(obstacleGrid[0])
        ans = []
        seen = [[False] * n for _ in range(m)]
        
        def dfs(r : int, c: int) -> bool:
            if r >= m or c >=n or obstacleGrid[r][c] == 1 or seen[r][c]:
                return False

            seen[r][c] = True
            if (r == m-1 and c == n-1) or dfs(r+1, c) or dfs(r, c+1):
                ans.append([r,c])
                return True
            
            return False
        
        dfs(0, 0)
        return ans[::-1]