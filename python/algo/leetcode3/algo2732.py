from typing import List

# https://leetcode.cn/problems/find-a-good-subset-of-the-matrix/solutions/2305490/xiang-xi-fen-xi-wei-shi-yao-zhi-duo-kao-mbl6a/?envType=daily-question&envId=2024-06-25
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