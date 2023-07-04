class Solution:
    m:int
    n:int
    def longestIncreasingPath(self, matrix) -> int:
        self.m = len(matrix)
        self.n = len(matrix[0])
        path = [[0] * (self.n) for _ in range(self.m)]
        for i in range(self.m):
            for j in range(self.n):
                self.setPath(i, j, matrix, path)
        maxPath = 1
        for i in range(self.m):
            for j in range(self.n):
                maxPath = max(maxPath, path[i][j])
        return maxPath

    def setPath(self, i:int, j:int, matrix, path) -> int:
        if path[i][j] > 0:
            return path[i][j]
        ijPath = 1
        if i - 1 >=0 and matrix[i][j] < matrix[i-1][j]:
            ijPath = max(ijPath, self.setPath(i-1, j, matrix, path) + 1)
        if i + 1 < self.m and matrix[i][j] < matrix[i+1][j]:
            ijPath = max(ijPath, self.setPath(i+1, j, matrix, path) + 1)
        if j - 1 >=0 and matrix[i][j] < matrix[i][j-1]:
            ijPath = max(ijPath, self.setPath(i, j-1, matrix, path) + 1)
        if j + 1 < self.n and matrix[i][j] < matrix[i][j+1]:
            ijPath = max(ijPath, self.setPath(i, j+1, matrix, path) + 1)
        path[i][j] = ijPath
        return ijPath


if __name__ == "__main__":
    sol = Solution()
    matrix = [[9,9,4],[6,6,8],[2,1,1]]
    print(sol.longestIncreasingPath(matrix))