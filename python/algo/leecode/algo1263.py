class Solution:
    def minPushBox(self, grid) -> int:
        m, n = len(grid), len(grid[0])
        dp = [[-1] * m * n for _ in range(m * n)]
        
        bx, by, sx, sy = 0, 0, 0, 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 'S':
                    sx, sy = i, j
                elif grid[i][j] == 'T':
                    tx, ty = i, j
                elif grid[i][j] == 'B':
                    bx, by = i, j
        
        dp[sx*n+sy][bx*n+by] = 0
        q = [(sx, sy, bx, by)]
        qi = []
        cur = 0
        while q or qi:
            if not q:
                q, qi = qi, q
                cur += 1
            
            _sx, _sy, _bx, _by = q.pop(0)
            for mx, my in [(0,1),(0,-1),(-1,0),(1,0)]:
                if 0 <= _sx + mx < m and 0 <= _sy + my < n and grid[_sx + mx][_sy + my] != '#':
                    if _sx + mx == _bx and _sy + my == _by:
                        if not (0 <= mx + _bx < m and 0 <= my + _by < n):
                            continue
                        elif grid[mx + _bx][my + _by] == 'T':
                            return cur + 1
                        elif grid[mx + _bx][my + _by] != '#':
                            dp[(_sx + mx)*n + _sy + my][(mx + _bx)*n+my + _by] = cur
                            qi.append((_sx + mx, _sy + my, mx + _bx, my + _by))
                    else:
                        if dp[(_sx + mx)*n + _sy + my][_bx*n + _by] == -1:
                            dp[(_sx + mx)*n + _sy + my][_bx*n + _by] = cur
                            q.append((_sx + mx, _sy + my, _bx, _by))

        return -1

if __name__ == "__main__":
    sol = Solution()
    grid = [["#","#","#","#","#","#"],
             ["#","T","#","#","#","#"],
             ["#",".",".","B",".","#"],
             ["#",".","#","#",".","#"],
             ["#",".",".",".","S","#"],
             ["#","#","#","#","#","#"]]
    
    grid = [["#",".",".","#","#","#","#","#"],["#",".",".","T","#",".",".","#"],["#",".",".",".","#","B",".","#"],["#",".",".",".",".",".",".","#"],["#",".",".",".","#",".","S","#"],["#",".",".","#","#","#","#","#"]]
    print(sol.minPushBox(grid))