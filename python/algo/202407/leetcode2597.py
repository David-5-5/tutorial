from collections import defaultdict
from typing import List


class Solution:
    # 方法一 子集型回溯, 时间复杂度 O(2^n)
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        ans = -1
        n = len(nums)
        d = defaultdict(int)
        def dfs(i:int) -> int:
            nonlocal ans
            if i == n:
                ans += 1
                return 
            
            # not select
            dfs(i+1)

            # select
            if d[nums[i]-k]==0 and d[nums[i]-k]==0:
                d[nums[i]] += 1
                dfs(i+1)
                d[nums[i]] -= 1
        
        dfs(0)
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [2,4,6], 2
    print(sol.beautifulSubsets(nums, k))