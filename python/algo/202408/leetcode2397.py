from typing import List


class Solution:
    def maximumRows(self, matrix: List[List[int]], numSelect: int) -> int:
        m, n = len(matrix), len(matrix[0])

        ans = 0
        for i in range(1 << n):
            res = 0
            if i.bit_count() != numSelect: continue
            for r in range(m):
                v = 0
                for c in range(n):
                    if matrix[r][c] == 1: v |= 1 << c
                if i | v == i: res += 1
            if ans < res: ans = res
        return ans

if __name__ == "__main__":
    sol = Solution()
    matrix, numSelect =[[0,0,0],[1,0,1],[0,1,1],[0,0,1]], 2
    print(sol.maximumRows(matrix, numSelect))