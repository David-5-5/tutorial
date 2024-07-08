from typing import List


class Solution:
    def swimInWater(self, grid) -> int:
        n = len(grid)
        # inx of dp means the minimize time for the positon of grid
        # inx = row * n + col
        dp = [float("inf")] * (n * n)

        # inx 0 is begin, so the dp[0] is grid[0][0]
        dp[0] = grid[0][0]

        todo = []
        todo.append((0,0))

        # bfs from (0,0)
        while todo:
            x, y = todo.pop(0)

            for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                if 0 <= x+_x < n and 0 <= y+_y < n: # the valid position
                    # from (x,y) compare the dp of up/down/left/right
                    # if decrease the maximize time, the change th dp and add 
                    # to travel list
                    if dp[(x+_x)*n+y+_y] > max(dp[x*n+y],grid[x+_x][y+_y]):
                        dp[(x+_x)*n+y+_y] = max(dp[x*n+y],grid[x+_x][y+_y])
                        todo.append((x+_x,y+_y))

        return dp[n*n-1]

    def swimInWater2(self, grid) -> int:
        n = len(grid)
        # bi search
        def dfs(cur:int, l: int, visited:List[bool]) -> bool:
            if cur == n * n - 1:
                if grid[n-1][n-1] <= l :return True
                else: return False
            
            visited[cur] = True
            
            x, y = cur // n, cur % n
            if grid[x][y] > l:
                return False
            for u, v in [(x+1,y), (x-1,y), (x, y+1), (x, y-1)]:
                if 0 <= u < n and 0 <= v < n and not visited[u*n+v] and dfs(u*n+v, l, visited):
                    return True
            return False

        right = max(max(row) for row in grid)
        left = min(min(row) for row in grid)

        while left <= right:  # 区间不为空

            mid = (left + right) // 2
            if dfs(0, mid, [False]*(n*n)):
                right = mid - 1  # 范围缩小到 [left, mid-1]
            else:
                left = mid + 1  # 范围缩小到 [mid+1, right]
        return left
        # return dfs(0, 15, [False]*(n*n))


if __name__ == "__main__":
    sol = Solution()
    grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
    print(sol.swimInWater(grid))
    print(sol.swimInWater2(grid))