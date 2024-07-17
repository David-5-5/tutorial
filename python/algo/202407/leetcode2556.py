from typing import List

# 是否存在两条路从 (0,0) 到达 (m-1,n-1)
# 每次遍历将途径点修改为 0, 第二次需要重新找一条路径，到达终点
# 
class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        
        def dfs(x:int, y:int) -> bool:
            if x == m-1 and y == n-1:
                return True
            grid[x][y] = 0
            return x+1 < m and grid[x+1][y] and dfs(x+1,y) or \
                y+1 < n and grid[x][y+1] and dfs(x,y+1) 
        return not dfs(0,0) or not dfs(0,0)

if __name__ == "__main__":
    sol = Solution()
    grid = [[1,1,1],[1,0,0],[1,1,1]]
    print(sol.isPossibleToCutPath(grid))