from itertools import accumulate
from typing import Counter, List


class Solution:
    def getLargestOutlier(self, nums: List[int]) -> int:
        nums.sort()
        n = len(nums)
        presum = list(accumulate(nums, initial=0))

        cnt = Counter(nums)

        suf = 0
        for i in range(n-1,-1,-1):
            ss = suf + presum[i]
            if ss % 2 == 0:
                ss //= 2
                if cnt[ss] > 1 or (cnt[ss] == 1 and ss != nums[i]):
                    return nums[i]
            suf += nums[i]
        # return nums[0]
        

    
if __name__ == "__main__":
    sol = Solution()
    nums = [-108,-108,-517]
    print(sol.getLargestOutlier(nums))