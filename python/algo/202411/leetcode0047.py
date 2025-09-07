from collections import Counter
from itertools import permutations
from typing import List

# 专题: 重复数据 全排列 
class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        return list(set(permutations(nums)))
    
if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,1]
    print(sol.permuteUnique(nums))    