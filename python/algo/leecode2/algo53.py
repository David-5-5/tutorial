from math import inf
from typing import List
class Solution:
    '''同算法 面试题16.17 '''
    def maxSubArray(self, nums: List[int]) -> int:
        # 
        res = nums[0]
        cul = nums[0]
        for i in range(1, len(nums)):
            if res < cul: res = cul
            if cul < 0:
                cul = nums[i]
            else:
                cul += nums[i]
        if res < cul: res = cul
        return res
    
    def maxSubArray2(self, nums: List[int]) -> int:
        # 前缀和及前缀和最小值
        res = nums[0]
        pre_mn = pre = 0
        
        for v in nums:
            pre += v
            if pre - pre_mn > res:
                res = pre - pre_mn
            if pre < pre_mn: pre_mn = pre

        return res


    def maxSubArray3(self, nums: List[int]) -> int:
        # 动态规划 dp[i] 表示以i为最后一个数字的连续和最大值
        # 状态转移方程为 dp[i+1] = max(dp[i] + nums[i+1], nums[i+1])
        # 最后，返回数组中的最大值即可
        n = len(nums)
        dp = [-inf] * n
        dp[0] = nums[0]
        for i in range(1, n):
            dp[i] = max(dp[i-1]+nums[i], nums[i])

        return max(dp)


    def maxSubArray4(self, nums: List[int]) -> int:
        # 分治算法
        n = len(nums)

        # 返回值为
        # mSum 表示 [l,r] 内的最大子段和 (需要的结果,从mSum可以推出其他的需要维护的变量信息)
        # lSum 表示 [l,r] 内以 l 为左端点的最大子段和
        # rSum 表示 [l,r] 内以 r 为右端点的最大子段和
        # iSum 表示 [l,r] 的区间和
        def get(l, r) -> tuple[int, int, int, int]:
            if l == r: return nums[l], nums[l], nums[l], nums[l]

            m = (l+r) // 2
            mSum_l, lSum_l, rSum_l, iSum_l = get(l,m)
            mSum_r, lSum_r, rSum_r, iSum_r = get(m+1,r)

            mSum = max(mSum_l, mSum_r, rSum_l + lSum_r)
            lSum = max(lSum_l, iSum_l + lSum_r)
            rSum = max(rSum_r, iSum_r + rSum_l)
            iSum = iSum_l + iSum_r
            return mSum, lSum, rSum, iSum

        return get(0, n-1)[0]
