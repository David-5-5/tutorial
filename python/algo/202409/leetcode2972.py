from typing import List

# 双周赛 120
class Solution:
    def incremovableSubarrayCount(self, nums: List[int]) -> int:
        # 参考题解 双指针
        n = len(nums)
        i, j = 0, n-1
        while i+1 < n and nums[i] < nums[i+1]:
            i += 1

        if i == n-1: return n * (n+1) // 2
        res = i + 2
        while j == n-1 or nums[j] < nums[j+1]:
            while i >= 0 and nums[i] >= nums[j]:
                i -= 1
            res += i + 2
            j -= 1
        return res

if __name__ == "__main__":
    sol = Solution()
    nums = [8,7,6,6]
    print(sol.incremovableSubarrayCount(nums))