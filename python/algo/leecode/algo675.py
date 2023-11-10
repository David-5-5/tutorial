from functools import lru_cache
import heapq

class Solution:
    def cutOffTree(self, forest) -> int:
        m, n = len(forest), len(forest[0])
        # dp[p1][p2]缓存两个单元格之间的最短距离，单个执行时间8s，力扣上执行需要3s。超时
        def distance(x1, y1, x2, y2):
            todo = [(0, x1 , y1)]
            # 增加visited，不使用dp需要引入已遍历的单元，使用dp时，由于对于
            # 已遍历的节点不会减少dp值，因此不会重复执行
            # visisted 为List 执行时间 36s
            # visisted 为List 使用bisect_right 维护一个有序列表 执行时间 3s
            # visisted 为Set 执行时间 2.5s
            visited = {(x1,y1)}
            while todo:
                step, x, y = todo.pop(0)
                if x == x2 and y == y2: return step

                for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0 <= x+_x < m and 0 <= y+_y < n and forest[x+_x][y+_y]>0 and (x+_x,y+_y) not in visited: 
                        todo.append((step+1, x+_x,y+_y))
                        visited.add((x+_x,y+_y))
                    # 以下是使用dp的写法
                    # if 0 <= x+_x < m and 0 <= y+_y < n and forest[x+_x][y+_y]>0: 
                    #     if dp[x1*n+y1][x*n+y] + 1 < dp[x1*n+y1][(x+_x)*n+y+_y]:
                    #         dp[x1*n+y1][(x+_x)*n+y+_y] = dp[x1*n+y1][x*n+y] + 1
                    #         if x+_x == x2 and y+_y == y2:break
                    #         todo.append((x+_x,y+_y))
                

            return -1
        
        # 官方使用sorted函数进行过滤并排序
        # trees = sorted((h, i, j) for i, row in enumerate(forest) for j, h in enumerate(row) if h > 1)
        # 比自行生成优先队列要快0.5s, 这0.5s决定是否能通过
        trees = []
        for i in range(m):
            for j in range(n):
                if forest[i][j] > 1:
                    heapq.heappush(trees, (forest[i][j], i, j))
        
        step = 0
        bx, by = 0, 0
        while trees:
            _, ex, ey = heapq.heappop(trees)
            dis = distance(bx, by, ex, ey)
            if dis < 0:
                return -1
            step += dis
            bx, by = ex, ey
        
        return step


    def cutOffTree2(self, forest) -> int:
        '''
        Official solution
        '''
        def bfs(sx: int, sy: int, tx: int, ty: int) -> int:
            m, n = len(forest), len(forest[0])
            from collections import deque
            q = deque([(0, sx, sy)])
            vis = {(sx, sy)}
            while q:
                d, x, y = q.popleft()
                if x == tx and y == ty:
                    return d
                for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
                    if 0 <= nx < m and 0 <= ny < n and forest[nx][ny] and (nx, ny) not in vis:
                        vis.add((nx, ny))
                        q.append((d + 1, nx, ny))
            return -1

        trees = sorted((h, i, j) for i, row in enumerate(forest) for j, h in enumerate(row) if h > 1)
        ans = preI = preJ = 0
        for _, i, j in trees:
            d = bfs(preI, preJ, i, j)
            if d < 0:
                return -1
            ans += d
            preI, preJ = i, j
        return ans
    



if __name__ == "__main__":
    sol = Solution()
    forest = [[54581641,64080174,24346381],
              [86374198,61363882,68783324],
              [668150,92178815,89819108]]

    # forest = [[1,2,3],[0,0,4],[7,6,5]]
    from datetime import datetime
    begin = datetime.now()
    print(sol.cutOffTree(forest))
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    print(sol.cutOffTree2(forest))
    print((datetime.now()- begin).total_seconds()) 