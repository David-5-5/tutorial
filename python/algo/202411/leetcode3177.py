from bisect import bisect_left
from collections import defaultdict
from functools import cache
from typing import List

# 双周赛 132
class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        
        if len(nums) == 1 : return 1
        v_pos = defaultdict(list)
        for i, v in enumerate(nums):
            v_pos[v].append(i)
        
        max_prev = [0] * (k+1)
        ans = 0
        @cache
        def dfs(i:int, c:int)-> int:
            if i < 0: return 0
            if i == 0: return 1

            if nums[i-1] == nums[i]: return 1 + dfs(i-1, c)

            inx = bisect_left(v_pos[nums[i]], i)
            if c == 0:
                return 1 + (dfs(v_pos[nums[i]][inx-1], c)if inx else 0)


            res = max(1+(dfs(v_pos[nums[i]][inx-1], c) if inx else 0), 1 + max_prev[c-1])
            max_prev[c] = max(max_prev[c], res)
            return res

        return max(dfs(i, k) for i in range(1, range(len(nums))))

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,4,5,1], 0
    nums, k = [1,2,1,1,3], 2
    nums, k = [15,6,26,32,6], 1
    print(sol.maximumLength(nums, k))