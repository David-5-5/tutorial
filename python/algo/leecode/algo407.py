import heapq

class Solution:
    def trapRainWater(self, heightMap) -> int:
        if (len(heightMap) <= 2 or len(heightMap[0]) <= 2): return 0

        n = len(heightMap)      # row
        m = len(heightMap[0])   # column


        visited = [[False for _ in range(m)] for _ in range(n)]
        pq = []
        for i in (0, n-1):
            for j in range(m):
                visited[i][j] = True
                heapq.heappush(pq, (heightMap[i][j], i*m + j))
        for j in (0, m-1):
            for i in range(1, n-1):
                visited[i][j] = True
                heapq.heappush(pq, (heightMap[i][j], i*m + j))

        adj = [0, -1, 0, 1, 0]
        res = 0
        while pq:
            height, postion = heapq.heappop(pq)
            for dev in range(4):
                px, py = postion // m + adj[dev], postion % m + adj[dev + 1]
                if px >= 0 and px < n and py >=0 and py < m and not visited[px][py]:
                    visited[px][py] = True
                    res += max(0, height - heightMap[px][py])
                    heapq.heappush(pq, (max(height, heightMap[px][py]), px * m + py))

        return res


    def trapRainWater2(self, heightMap) -> int:
        if (len(heightMap) <= 2 or len(heightMap[0]) <= 2): return 0

        n = len(heightMap)      # row
        m = len(heightMap[0])   # column

        maxHeight = max(max(row) for row in heightMap)

        waterHeight = [[maxHeight for _ in range(m)] for _ in range(n)]
        queue = []
        for i in (0, n-1):
            for j in range(m):
                if waterHeight[i][j] > heightMap[i][j]:
                    waterHeight[i][j] = heightMap[i][j]
                    queue.append((i,j))
        for j in (0, m-1):
            for i in range(1, n-1):
                if waterHeight[i][j] > heightMap[i][j]:
                    waterHeight[i][j] = heightMap[i][j]
                    queue.append((i,j))
        
        adj = [0, -1, 0, 1, 0]
        while queue:
            px, py = queue.pop(0)
            for dev in range(4):
                adjx = px + adj[dev]
                adjy  = py + adj[dev + 1]
                if adjx < 0 or adjx >= n or adjy < 0 or adjy >= m:
                    continue
                if  waterHeight[adjx][adjy] > waterHeight[px][py] and waterHeight[adjx][adjy] > heightMap[adjx][adjy]:
                    waterHeight[adjx][adjy] = max(waterHeight[px][py], heightMap[adjx][adjy])
                    queue.append((adjx, adjy))

        res = 0
        for i in range(n):
            for j in range(m):
                res += waterHeight[i][j] - heightMap[i][j]
        
        return res




if __name__ == "__main__":
    sol = Solution()
    # input = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
    input = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
    print(sol.trapRainWater(input))
    print(sol.trapRainWater2(input))
