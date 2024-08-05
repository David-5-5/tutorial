from typing import List

# 周赛 325 
# 正难则反，背包计数的模板方法
class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:

        if sum(nums) < 2 * k: return 0

        MOD = 10 ** 9 + 7
        f = [0] * k
        f[0] = 1
        for i in range(len(nums)):
            for j in range(k-1, -1, -1):
                if j >= nums[i]:
                    f[j] += f[j-nums[i]]
        
        ans = pow(2, len(nums), MOD)
        return (ans - 2 * sum(f)) % MOD
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,4], 4
    print(sol.countPartitions(nums, k))