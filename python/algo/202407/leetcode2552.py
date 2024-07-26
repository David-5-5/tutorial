from typing import List

# 周赛330 技巧题
class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        # i < j < k < l
        # nums[i] < nums[k] < nums[j] < nums[l]
        # great[][] 表示在下标 k 的右边大于 nums[j] 的数的数量
        # less[][] 表示在下标 j 的左边 小于 nums[k] 的数的数量
        n = len(nums)
        
        great = [0] * n
        great[-1] = [0] * (n + 1)
        
        for k in range(n-2, -1, -1): # 遍历下标
            great[k] = great[k+1][:]
            for x in range(1, nums[k+1]):  # 遍历数的值域 
                great[k][x] += 1
        
        less = [0] * (n + 1)
        ans = 0
        for j in range(1, n-1):
            for x in range(nums[j-1], n+1):  # 遍历数的值
                less[x] += 1
            for k in range(j+1, n-1):
                if nums[j] > nums[k]:
                    ans += less[nums[k]] * great[k][nums[j]]

        return ans % (10**9 + 7)

if __name__ == "__main__":
    sol = Solution()
    nums = [1,3,2,4,5]
    print(sol.countQuadruplets(nums))