from collections import defaultdict
from typing import List

# 周赛 356
class Solution:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        ans, l, dc, cnt, win = 0, 0, len(set(nums)), defaultdict(int), set()

        for r, v in enumerate(nums):
            win.add(v)
            cnt[v] += 1
            if len(win) < dc: continue

            while l < r and cnt[nums[l]] > 1:
                cnt[nums[l]] -= 1
                l += 1
            
            ans += l + 1
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,3,1,2,2]
    nums = [5,5,5,5]
    print(sol.countCompleteSubarrays(nums))