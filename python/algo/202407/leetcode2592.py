from typing import List

# 自行解答
class Solution:
    def maximizeGreatness(self, nums: List[int]) -> int:
        n = len(nums)
        # 排序数组，排序不影响结果，可以排序
        nums.sort()
        ans = 0
        j = n
        while j:
            # j从n-1开始遍历，尽量比较最大值
            if nums[n-ans-1] > nums[j-1]: # 满足条件 ans增加 1
                ans += 1
            j -= 1 # 尝试下一个小于nums[n-ans-1]的最大值
        return ans

if __name__ == "__main__":
    solution = Solution()
    nums = [1, 2, 3, 4, 5, 6]
    print(solution.maximizeGreatness(nums))