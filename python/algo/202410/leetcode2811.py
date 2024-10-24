from functools import cache
from itertools import accumulate
from typing import List

# 周赛 357
class Solution:
    def canSplitArray(self, nums: List[int], m: int) -> bool:
        # 自行解答，DP
        presum = list(accumulate(nums, initial=0))
        
        @cache
        def dfs(i:int, j:int) -> bool:
            
            if i+1 == j: return True
            
            for k in range(i+1, j):
                if (i+1==k or presum[k] - presum[i] >= m) and (k+1==j or presum[j]-presum[k]>=m) and dfs(i,k) and dfs(k,j):
                    return True

            return False
        
        return dfs(0, len(nums))
    
if __name__ == "__main__":
    sol = Solution()
    nums, m = [2,2,1], 4
    print(sol.canSplitArray(nums, m))