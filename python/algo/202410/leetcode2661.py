from typing import List

# 周赛 343
class Solution:
    def firstCompleteIndex(self, arr: List[int], mat: List[List[int]]) -> int:
        # 自行解答
        m, n = len(mat), len(mat[0])
        row = [0] * m
        col = [0] * n
        pos = dict()

        for r in range(m):
            for c in range(n):
                pos[mat[r][c]] = (r,c)

        for i, v in enumerate(arr):
            r, c = pos[v]
            row[r] += 1
            col[c] += 1
            if row[r] == n: return i
            if col[c] == m: return i
        
if __name__ == "__main__":
    sol = Solution()
    arr, mat = [1,3,4,2], [[1,4],[2,3]]
    print(sol.firstCompleteIndex(arr, mat))
