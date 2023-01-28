import heapq
class Solution:
    def maxPoints(self, grid, queries):
        rows, cols = len(grid), len(grid[0])
        count = len(queries)
        ret = [0] * count
        heap = [(grid[0][0], 0,0)]
        grid[0][0] = 0
        points = 0
        for qi, q in sorted(enumerate(queries), key=lambda p:p[1]):
            while heap and heap[0][0] < q:
                points += 1
                _, row, col = heapq.heappop(heap)

                # Up of current in grid
                if row-1 >=0 and grid[row-1][col]:
                    heapq.heappush(heap, (grid[row-1][col], row-1, col))
                    grid[row-1][col] = 0
                # Down of current in grid
                if row+1 < rows and grid[row+1][col]:
                    heapq.heappush(heap, (grid[row+1][col], row+1, col))
                    grid[row+1][col] = 0
                # Left of current in grid
                if col-1 >= 0 and grid[row][col-1]:
                    heapq.heappush(heap, (grid[row][col-1], row, col-1))
                    grid[row][col-1] = 0
                # Right of current in grid
                if col+1 < cols and grid[row][col+1]:
                    heapq.heappush(heap, (grid[row][col+1], row, col+1))
                    grid[row][col+1] = 0
            ret[qi] = points
        return ret

    def maxPoints2(self, grid, queries):
        rows, cols = len(grid), len(grid[0])
        count = len(queries)
        ret = [0] * count
        heap = [(grid[0][0], 0,0)]
        grid[0][0] = 0
        points = 0
        for qi, q in sorted(enumerate(queries), key=lambda p:p[1]):
            while heap and heap[0][0] < q:
                points += 1
                _, row, col = heapq.heappop(heap)

                # Up, Dow, right ,left of current in grid
                for x, y in (row-1, col), (row+1, col),(row, col-1), (row,col+1):
                    if 0 <= x < rows and 0 <=y < cols and grid[x][y]:
                        heapq.heappush(heap, (grid[x][y], x, y))
                        grid[x][y] = 0
            ret[qi] = points
        return ret

if __name__ == "__main__":
    sol = Solution()
    grid = [[1,2,3],[2,5,7],[3,5,1]]
    queries = [5,6,2]
    print(sol.maxPoints2(grid, queries))
