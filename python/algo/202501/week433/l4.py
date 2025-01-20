from typing import List

# 3430 简化版本 907
class Solution:
    def minMaxSubarraySum(self, nums: List[int], k: int) -> int:
        # 参考题解
        n = len(nums)
        
        # 模板 单调栈计算 最小值/最大值的左右区间 两次遍历
        # left, right, st = [-1] * n, [n] * n, []
        # for i, v in enumerate(nums):
        #     while st and nums[st[-1]] >= v: # 相同元素左边 >= 
        #         st.pop()
        #     if st: left[i] = st[-1]
        #     st.append(i)
        # st = []
        # for i in range(n-1, -1, -1):
        #     while st and nums[st[-1]] > nums[i]: # 相同元素右边 >
        #         st.pop()
        #     if st: right[i] = st[-1]
        #     st.append(i)
        # 单调栈计算 最小值/最大值的左右区间 一次遍历, 其中：
        # 1, >= v 求最小值 
        # 2, <= v 求最大值
        # # for i, v in enumerate(nums): 
        #     while st and nums[st[-1]] >= v: right[st.pop()] = i
        #     if st: left[i] = st[-1]
        #     st.append(i)

        # 优化后的代码
        def calculate(isMin: bool) -> int:
            left, right, st = [-1] * n, [n] * n, []
            for i, v in enumerate(nums):
                if isMin:
                    while st and nums[st[-1]] <= v: right[st.pop()] = i
                else:
                    while st and nums[st[-1]] >= v: right[st.pop()] = i
                if st: left[i] = st[-1]
                st.append(i)
            res = 0

            for i, v in enumerate(nums):
                l, r = min(i - left[i], k), min(right[i] - i, k)
                if l + r <= k + 1:
                    cnt = l * r
                else:
                    cnt = r * (k+1-r) # l' + r <= k+1
                    cnt += (r-1 + k+1 - l) * (l+r-k-1) // 2 # L取 l' + 1, l+2, ... l
                res += cnt * v
            return res
        
        ans = calculate(True)
        ans += calculate(False)

        return ans  