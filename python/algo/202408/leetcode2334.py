from math import floor, inf
from typing import List

# 双周赛 82 参考题解
class Solution:
    def validSubarraySize(self, nums: List[int], threshold: int) -> int:
        # 并查集
        n = len(nums)
        fa = list(range(n+1))
        sz = [1] * n
        
        def find(x:int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]
        
        for i, num in sorted(enumerate(nums), key=lambda p:p[1], reverse=True):
            # merge i, i+1
            # i+1并不参与计算，一边合并一边计算，没有经过训练，根本做不出来
            j = find(i+1)
            fa[i] = j
            sz[j] += sz[i]
            if num > threshold / (sz[j]-1): # 排除末端的 i+1
                return sz[j]-1
        return -1

    def validSubarraySize2(self, nums: List[int], threshold: int) -> int:
        # 单调栈
        n = len(nums)
        left,st = [-1] * n, []
        for i, num in enumerate(nums):
            while st and nums[st[-1]] >= num: st.pop()
            if st: left[i]=st[-1]
            st.append(i)
        
        right, st = [n] * n, []
        for i in range(n-1,-1,-1):
            while st and nums[st[-1]] >= nums[i]: st.pop()
            if st: right[i]=st[-1]
            st.append(i)

        for num, l, r in zip(nums,left, right):
            if num > threshold / (r - l - 1):
                return r - l - 1
        return -1

if __name__ == "__main__":
    sol = Solution()
    nums, threshold = [1,3,4,3,1], 6
    print(sol.validSubarraySize(nums, threshold))
    print(sol.validSubarraySize2(nums, threshold))