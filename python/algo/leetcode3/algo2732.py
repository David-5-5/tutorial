from typing import List

class Solution:
    def goodSubsetofBinaryMatrix(self, grid: List[List[int]]) -> List[int]:

        mask_to_idx = {}
        for i, row in enumerate(grid):
            mask = 0
            for j, v in enumerate(row):
                mask |= v << j
            if mask == 0:
                return [i]
            mask_to_idx[mask] = i
        
        for x, i in mask_to_idx.items():
            for y, j in mask_to_idx.items():
                if x & y == 0:
                    return sorted((i,j))
        return []

if __name__ == "__main__":
    sol = Solution()
    print(sol.goodSubsetofBinaryMatrix([[0,1,1,0],[0,0,0,1],[1,1,1,1]]))            