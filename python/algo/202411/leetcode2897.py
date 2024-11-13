from typing import List

# 周赛 366
class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        # 参考题解
        # AND 和 OR 操作的性质
        # 假定 nums[i] < nums[j]
        # nums[i] = nums[i] AND nums[j]
        # nums[j] = nums[i] OR nums[j]
        # 实质上将 nums[i] 为 1 的比特 转移到 nums[j] 为 0 的比特上
        # 转移后 nums[i] 和 nums[j] 中包含的 1 的数量不变
        # (nums[i] - d)^2 + (nums[j]+d) ^ 2 
        # = nums[i]^2 + nums[j]^2 + (nums[j]-nums[i]) * d + d^2
        # >= nums[i]^2 + nums[j]^2
        # 因此统计nums上所位上 1 的数量，然后取 k 次从各位取 1 组成尽量大的数
        MOD = 1_000_000_007

        cnt = [0] * 32
        for v in nums:
            i = 0
            while v:
                if v & 1:cnt[i]+=1
                i += 1
                v //= 2

        ans = 0
        for _ in range(k):
            cur = 0
            for i in range(32):
                if cnt[i]:
                    cur += pow(2,i)
                    cnt[i] -= 1
            if cur == 0:break
            ans = (ans + pow(cur,2)) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [4,5,4,7], 3
    print(sol.maxSum(nums, k))