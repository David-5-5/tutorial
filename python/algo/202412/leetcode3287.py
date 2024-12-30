from functools import reduce
from operator import or_
from typing import List

# 双周赛 139
class Solution:
    def maxValue(self, nums: List[int], k: int) -> int:
        # 参考题解 动态规划 刷表法
        # f(i,j,x) 表示从前 i 个元素中选出 j 个，OR 起来能否得到 x
        # g(i,j,x) 表示从第 i 个元素到最后一个元素中选出 j 个，OR 起来能否得到 x
        # 转移方程:
        # f(i, j, x) -> f(i + 1, j, x) // 不选 nums[i]
        # f(i, j, x) -> f(i + 1, j + 1, x | nums[i]) // 选 nums[i]
        # 上面这种写法称为刷表法, 填表法 f(i, j, y|nums[i]) -> f(i + 1, j + 1, x )
    
        n, m = len(nums), reduce(or_, nums) + 1
        pre = [[[False] * (m) for _ in range(k+1)] for _ in range(n-k+1)]
        suf = [[[False] * (m) for _ in range(k+1)] for _ in range(n-k+1)]
        pre[0][0][0] = suf[0][0][0] = True

        for i in range(n-k):                # 尽量减少 i 和 j 
            for j in range(min(i+1,k+1)):   # 的取值范围，减少执行时间
                for x in range(m):
                    if pre[i][j][x]:
                        pre[i+1][j][x] = pre[i][j][x] # 不选 nums[i]
                        # 关键点 j 的 循环区间为 [0,k],保证不选的情况下，j == k
                        if (j+1)<=k:pre[i+1][j+1][x|nums[i]] = pre[i][j][x]    # 选 nums[n-i-1]
                    if suf[i][j][x]:
                        suf[i+1][j][x] = suf[i][j][x] # 不选 nums[n-i-1]
                        if (j+1)<=k: suf[i+1][j+1][x|nums[n-i-1]] = suf[i][j][x] # 选 nums[n-i-1]

        ans = 0
        for i in range(k, n-k+1):
            for x in range(m):
                for y in range(m):
                    if pre[i][k][x] and suf[n-i][k][y]:
                        ans = max(ans, x^y)
        return ans