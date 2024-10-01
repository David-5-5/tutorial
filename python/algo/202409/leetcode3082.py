from typing import List

# 双周赛 126
class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        # 参考题解的方法：使用二维背包，自行解答
        # 题目转换为 容量为 k 的背包，按照物品的数量放入的数量
        # 例如：放入 1 个 num 的数量，2 个num的数量， 3...
        # 然后在计算 t 个num可以在多少个子序列中，包含 t 个num的子序列数量
        # 为 2 ** (n-t)
        # ans = sum(count_i * (2 ** (n - t_i)))
        MOD = 10 ** 9 + 7
        n = len(nums)
        nums.sort()
        dp = [[0] * (k+1) for _ in range(k+1)]
        dp[0][0] = 1
        for v in nums:
            if v > k: break
            for j in range(k, v-1,-1):
                for c in range(1, k+1):
                    dp[j][c] = (dp[j][c] + dp[j-v][c-1]) % MOD
        
        ans = 0
        for c in range(1, k+1):
            ans += dp[k][c] * pow(2, n - c, MOD)
        return ans % MOD
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3], 3
    print(sol.sumOfPower(nums, k))