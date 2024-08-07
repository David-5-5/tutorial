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
    
    def maximumRows2(self, matrix: List[List[int]], numSelect: int) -> int:
        # 题解写法, 更简洁，更优雅，更python
        mask = [sum(v << j for j, v in enumerate(row)) for row in matrix]
        ans = 0
        for i in range(1 << len(matrix[0])):
            if i.bit_count() != numSelect: continue
            ans = max(ans, sum(i | row == i for row in mask))
        return ans

    def maximumRows3(self, matrix: List[List[int]], numSelect: int) -> int:
        # Gosper's hack
        x = (1 << numSelect) - 1
        

if __name__ == "__main__":
    sol = Solution()
    matrix, numSelect =[[0,0,0],[1,0,1],[0,1,1],[0,0,1]], 2
    print(sol.maximumRows(matrix, numSelect))
    print(sol.maximumRows2(matrix, numSelect))