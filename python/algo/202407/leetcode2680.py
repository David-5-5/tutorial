from typing import List


class Solution:
    def maximumOr(self, nums: List[int], k: int) -> int:
        # 前后缀分解
        n = len(nums)
        suf = [0] * (n + 1)
        for i in range(n-1, 0, -1):
            suf[i] = suf[i+1] | nums[i]
        
        ans = pre = 0
        for i in range(n):
            ans = max(ans, pre | suf[i+1] | nums[i] << k)
            pre = pre | nums[i]
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, k = [12,9], 1
    print(sol.maximumOr(nums, k))