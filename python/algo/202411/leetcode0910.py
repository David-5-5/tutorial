from typing import List

# 贪心专题
class Solution:
    def smallestRangeII(self, nums: List[int], k: int) -> int:
        # 参考题解，排序
        # 小的变大，大的变小
        # 初始值为 nums[n-1] - nums[0]
        # 在 i 处分界 nums[0] ~ nums[i-1] +k, nums[i]~ nums[n-1]-k
        # 这样最大值为 max(nums[i-1]+k, nums[n-1]-k)
        #    最小值为 min(nums[i]-k, nums[0] + k)
        # 枚举 i，得到最小的 差值
        nums.sort()

        ans, n, c_mx, c_mn = nums[-1]-nums[0], len(nums), nums[-1]-k, nums[0]+k
        for i in range(1, n):
            ans = min(ans, max(nums[i-1]+k,c_mx) - min(nums[i]-k,c_mn))
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [0, 10], 2

    print(sol.smallestRangeII(nums, k))