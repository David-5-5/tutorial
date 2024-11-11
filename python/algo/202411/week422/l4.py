from collections import defaultdict
from functools import cache
from math import perm
from typing import List

"""
参考题解，解题思路
排列问题 转换为 组合问题 + 一般排列

组合问题 => 子序列问题 => 恰好型 0-1 背包问题
寻找 floor(n/2) 个数的和等于 sum(num) // 2

背包的方案数 * floor(n/2)! * (n-floor(n/2))! / cnt[0]! ... cnt[9]!
注：不需要对每个方案统计奇偶序列的重复数字的数量，
   只需要计算全部重复数字的数量，而这对于所有方案是相同的
    
"""
class Solution:
    def countBalancedPermutations(self, num: str) -> int:
        MOD = 10 ** 9 + 7
        cnt = [0] * 10
        nums = [int(v) for v in num]
        for v in num:
            cnt[int(v)] += 1
        
        n = len(nums)
        total = sum(nums)

        if total % 2: return 0

        # 多维条件计算 0-1 背包
        @cache
        def dfs(i:int, left_cnt:int, left_sum:int) -> int:
            if i == n or left_cnt == 0:
                if left_cnt == 0 and left_sum == 0:return 1
                else: return 0

            res = dfs(i+1, left_cnt - 1, left_sum - nums[i]) # 选
            res += dfs(i+1, left_cnt, left_sum) #不选
            return res
        
        res = dfs(0, n//2, total//2)
        dfs.cache_clear()
        ans = res * perm(n//2) * perm(n-n//2) % MOD
        
        # 求逆元
        for c in cnt:
            ans = ans * pow(perm(c), MOD-2, MOD) % MOD

        return ans
        

if __name__ == "__main__":
    sol = Solution()
    num = "123"
    print(sol.countBalancedPermutations(num))