class Solution:
    def checkPossibility(self, nums: list[int]) -> bool:
        n, cnt = len(nums), 0
        for i in range(n-2, -1, -1):
            if nums[i] > nums[i+1]:
                if cnt == 1: return False
                cnt = 1
                if i < n - 2:
                    if nums[i] > nums[i+2]:
                        nums[i] = nums[i+1]
        return True
