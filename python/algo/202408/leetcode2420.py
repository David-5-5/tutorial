from typing import List

# 周赛 312
class Solution:
    def goodIndices(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        inc = [1] * n
        for i in range(n-1):
            if nums[i] <= nums[i+1]:
                inc[i+1] = inc[i] + 1
        dec, ans = 1, []
        for i in range(1, n-k):
            if dec >=k and inc[i+k]>=k:
                ans.append(i)
            if nums[i] <= nums[i-1]:
                dec += 1
            else:
                dec = 1
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, k = [2,1,1,1,3,4,1], 2
    print(sol.goodIndices(nums, k))

