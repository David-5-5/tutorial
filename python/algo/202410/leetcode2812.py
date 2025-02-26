from bisect import bisect_left
from typing import List

# 周赛 357
class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        # 参考题解
        # 步骤一每个单元格的最大安全路径，可以使用 从存在小偷的节点出发，广度优先搜索
        # 步骤二从 (0,0) 到 (n-1,n-1) 之间的最短路径
        #   方法一 二分搜索
        #   方法二 并查集

        n, q = len(grid), []
        # 初始化
        dis = [[-1] * n for _ in range(n)]
        for r in range(n):
            for c in range(n):
                if grid[r][c] == 1:
                    dis[r][c] = 0
                    q.append((r,c))
        
        # BFS 生成各单元格的最长安全距离
        cur = 1
        while q:
            tmp = q
            q = []
            for r, c in tmp:
                for nr, nc in [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]:
                    if 0 <= nr < n and 0 <= nc < n and dis[nr][nc] == -1:
                        dis[nr][nc] = cur
                        q.append((nr, nc))
            cur += 1
        
        vis = [[0] * n for _ in range(n)]
        # 使用 clock 时间戳 只需要复用一个 vis 数组
        clock = 0
        
        def check(mx:int) -> bool:
            nonlocal clock
            clock += 1
            def dfs(r:int, c:int) -> bool:
                if r==n-1 and c == n-1:
                    if dis[r][c] < mx: return False
                    else: return True
                
                vis[r][c] = clock
                if dis[r][c] < mx: return False
                
                for nr, nc in [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]:
                    if 0 <= nr < n and 0 <= nc < n and vis[nr][nc] < clock and dfs(nr, nc):
                        return True
                return False
            
            return dfs(0, 0)
        
        l , r = -1, cur # 使用 cur 代替 2n-2 
        while l + 1 < r:
            mid = (l+r) // 2
            if check(mid):
                l = mid
            else:
                r = mid
        return l
        # return bisect_left(range(r), True, key=check) # 不通过??
    
    def maximumSafenessFactor2(self, grid: List[List[int]]) -> int:
        # 同 maximumSafenessFactor，第二步使用并查集

        n, q = len(grid), []
        # 初始化
        dis = [[-1] * n for _ in range(n)]
        for r in range(n):
            for c in range(n):
                if grid[r][c] == 1:
                    dis[r][c] = 0
                    q.append((r,c))
        
        # BFS 生成各单元格的最长安全距离
        cnt, cur = {}, 0
        cnt[cur] = q
        while q:
            tmp = q
            cur += 1
            q = []
            for r, c in tmp:
                for nr, nc in [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]:
                    if 0 <= nr < n and 0 <= nc < n and dis[nr][nc] == -1:
                        dis[nr][nc] = cur
                        q.append((nr, nc))
            if q: cnt[cur] = q

        adt = [-1] * (n*n)
        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]
        
        def union(x:int, y:int) -> int:
            root1 = find(x)
            root2 = find(y)
            if root1 == root2:
                return -adt[root1]
            adt[root2] = root1

            return -adt[root1]


        for mx in sorted(cnt.keys(), reverse=True):
            len_s = len(cnt[mx])
            for i in range(len_s):
                r, c = cnt[mx][i]
                for nr, nc in [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]:
                    if 0 <= nr < n and 0 <= nc < n and dis[nr][nc] >= mx:
                        union(r*n+c, nr*n+nc)

            if find(0) == find(n*n-1): return mx
        return 0

if __name__ == "__main__":
    sol = Solution()
    grid = [[0,0,1],[0,0,0],[0,0,0]]
    grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
    print(sol.maximumSafenessFactor(grid))
    print(sol.maximumSafenessFactor2(grid))

