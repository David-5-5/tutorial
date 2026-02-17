from bisect import bisect_left
from cmath import inf
from typing import List

class Solution:
    def challengeOfTheKeeper(self, maze: List[str]) -> int:
        n = len(maze)
        dis = [[inf] * n for _ in range(n)]

        st, end = (0, 0), (0, 0)
        for i in range(n):
            for j in range(n):
                if maze[i][j] == 'S':
                    st = (i, j)
                if maze[i][j] == 'T':
                    end = (i, j)

        q = [(end[0], end[1])]
        step, dis[end[0]][end[1]] = 1, 0
        while q:
            tmp = q
            q = []
            for x, y in tmp:
                for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0<=x+_x<n and 0<=y+_y<n and maze[x+_x][y+_y]!='#' \
                    and dis[x+_x][y+_y] == inf:
                        dis[x+_x][y+_y] = step
                        q.append((x+_x, y+_y))
            step += 1
        
        if dis[st[0]][st[1]] == inf: return -1
        if dis[st[0]][st[1]] == 1: return 0
        
        def mirror_len(x, y):
            mirror = 0
            if maze[x][y] != '.':return mirror
            if  maze[x][n-1-y] != '#':
                mirror = max(mirror, dis[x][n-y-1])
            if maze[n-x-1][y] != '#':
                mirror = max(mirror, dis[n-x-1][y])
            return mirror

        def check(mid: int)  -> bool:
            vis = [[False]*n for _ in range(n)]
            def dfs(x: int, y: int) -> bool:
                if maze[x][y] == '.' and mirror_len(x, y) > mid: return False
                if x == end[0] and y == end[1]: return True
                for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0<=x+_x<n and 0<=y+_y<n and maze[x+_x][y+_y]!='#' \
                        and not vis[x+_x][y+_y]:
                        vis[x+_x][y+_y] = True
                        if dfs(x+_x, y+_y): return True
                return False
            return dfs(st[0], st[1])

        # l, r = 0, n * n + 1
        # while l + 1 < r:
        #     mid = (l + r) // 2
        #     if check(mid): r = mid
        #     else: l = mid

        r = bisect_left(range(n * n + 1), True, key=check)
        return -1 if r > n*n else r



if __name__ == "__main__":
    sol = Solution()
    maze = [".....","##S..","...#.","T.#..","###.."]
    print(sol.challengeOfTheKeeper(maze))