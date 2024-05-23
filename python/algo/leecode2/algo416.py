from typing import List
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        # 使用 0-1 背包算法
        # 背包能够容纳的 w 为 nums的和的一半，其每个元素的价值 v[i] = w[i]
        # 因此当dp[w] = v = w 时，返回 True
        s_nums = sum(nums)
        n = len(nums)

        if s_nums % 2 == 1:return False

        w = s_nums // 2
        dp = [0] * (w+1)
        for i in range(n):
            for l in range(w, 0,-1):
                if l >= nums[i] and dp[l-nums[i]] + nums[i] > dp[l]:
                    dp[l] = dp[l-nums[i]] + nums[i]
                # 上面的写法性能要高很多
                # if l >= nums[i] :
                #     dp[l] = max(dp[l], dp[l-nums[i]] + nums[i])

        
        if dp[-1] == w : return True

        return False

if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,3,4,5,6,7]
    print(sol.canPartition(nums))