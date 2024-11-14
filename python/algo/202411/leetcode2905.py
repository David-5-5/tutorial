from collections import deque
from typing import List

# 周赛 367
class Solution:
    def findIndices(self, nums: List[int], indexDifference: int, valueDifference: int) -> List[int]:
        # 自行解答
        pre_mx = pre_mn = 0 # 前缀最大值，前缀最小值的下标
        # 后缀最大值(单调递减）及最小值（单调递增）的单调队列
        suf_mx, suf_mn = deque(), deque()

        n = len(nums)
        inx_d = indexDifference
        for i in range(inx_d, n):
            pre_i = i - inx_d
            # 更新前缀最大值下标
            if nums[pre_i] > nums[pre_mx]:
                pre_mx = pre_i
            # 更新前缀最大值下标
            if nums[pre_i] < nums[pre_mn]:
                pre_mn = pre_i

            # 更新后缀最大值队列
            while suf_mx and nums[suf_mx[-1]] <= nums[i]:
                suf_mx.pop()
            suf_mx.append(i)
            while suf_mx and suf_mx[0] < pre_mn + inx_d:
                suf_mx.popleft()
            # 比较前缀最小值和后缀最大值的差
            if abs(nums[pre_mn] - nums[suf_mx[0]]) >=valueDifference:
                return [pre_mn, suf_mx[0]]
             
            # 更新后缀最小值队列
            while suf_mn and nums[suf_mn[-1]] >= nums[i]:
                suf_mn.pop()
            suf_mn.append(i)
            while suf_mn and suf_mn[0] < pre_mx + inx_d:
                suf_mn.popleft()

            # 比较前缀最大值和后缀最小值的差
            if abs(nums[pre_mx] - nums[suf_mn[0]]) >=valueDifference:
                return [pre_mx, suf_mn[0]]
             
        return [-1,-1]


    
if __name__ == "__main__":
    sol = Solution()
    nums, indexDifference, valueDifference = [1,1,0,2,8,1,5,6,10,10], 4, 10
    print(sol.findIndices(nums, indexDifference, valueDifference))
    print(sol.findIndices2(nums, indexDifference, valueDifference))