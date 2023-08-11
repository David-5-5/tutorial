class Solution:
    def shortestPathAllKeys(self, grid) -> int:
        '''
        动态规划 + 状态压缩
        dp[keys][position] 初始为最大值 inf
        keys = a ~ f : 1 ~ 32
        keys = key1 | key2|... key3
        position = x * n + y

        dp[0][position of @] = 0
        bfs, 广度遍历算法 在每个坐标的上下左右
        dp[keys][x,y] + 1 小于 的下个位置 dp[keys][x',y']当前值, 
        更新dp[keys][x',y']值, 并将(x',y')加入广度搜索列表中, 
        否则忽略 同一keys值下, 仅遍历一次, 避免循环
        '''
        _keys, _locks = ['a', 'b', 'c', 'd', 'e', 'f'], ['A', 'B', 'C', 'D', 'E', 'F']
        keys, locks = [], []
        start = (0, 0)
        m, n = len(grid), len(grid[0])

        for i in range(m):
            for j in range(n):
                if grid[i][j] == '@':
                    start = (i, j)
                elif grid[i][j] in _keys:
                    keys.append(grid[i][j])
                elif grid[i][j] in _locks:
                    locks.append(grid[i][j])

        dp = [[float("inf") for _ in range(m * n)] for _ in range (1 << len(keys))]
        
        dp[0][start[0]*n+start[1]] = 0

        tovis = []
        tovis.append((0,0,start[0],start[1]))
        def bfs():
            while tovis:
                bin_key, path, x, y = tovis.pop(0)
                for _x, _y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    if 0 <= x+_x < m and 0 <= y+_y < n:
                        if grid[x+_x][y+_y] in ('.', '@'):
                            if dp[bin_key][(x+_x)*n+y+_y] > path + 1:
                                dp[bin_key][(x+_x)*n+y+_y] = path + 1
                                tovis.append((bin_key, path + 1, x+_x, y+_y))
                        if grid[x+_x][y+_y] in keys:
                            new_bin_key = bin_key | (1 << ord(grid[x+_x][y+_y]) - ord('a'))
                            if dp[new_bin_key][(x+_x)*n+y+_y] > path + 1:
                                dp[new_bin_key][(x+_x)*n+y+_y] = path + 1
                                if new_bin_key != (1 << len(keys)) - 1:
                                    tovis.append((new_bin_key, path + 1, x+_x, y+_y))
                        if grid[x+_x][y+_y] in locks:
                            if bin_key & (1 << ord(grid[x+_x][y+_y]) - ord('A')) and dp[bin_key][(x+_x)*n+y+_y] > path + 1:
                                dp[bin_key][(x+_x)*n+y+_y] = path + 1
                                tovis.append((bin_key, path + 1, x+_x, y+_y))

        bfs()
        ret = min(dp[(1 << len(keys))-1])
        return -1 if ret == float("inf") else ret
    
if __name__ == "__main__":
    sol = Solution()
    grid = ["@.a.#","###.#","b.A.B"]
    # grid = ["@..aA","..B#.","....b"]
    # grid = ["@Aa"]
    # grid = ["b","A","a","@","B"]
    grid = ["@...a",".###A","b.BCc"]
    grid = ["@fedcbBCDEFaA"]
    print(sol.shortestPathAllKeys(grid))