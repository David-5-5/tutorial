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

if __name__ == "__main__":
    sol = Solution()
    grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
    print(sol.swimInWater(grid))