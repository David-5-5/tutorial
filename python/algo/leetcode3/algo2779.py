from typing import List


class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()
        l = r = 0

        ans = 0
        while r < n:
            if nums[r]-nums[l] > 2 * k:
                l += 1
            else:
                ans = max(ans, r-l+1)
                r += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.maximumBeauty([4,6,1,2], 2))    