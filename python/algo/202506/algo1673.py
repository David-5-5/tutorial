from typing import List

# 常用数据结构 - 3.7 单调栈 - 最小字典序
class Solution:
    def mostCompetitive(self, nums: List[int], k: int) -> List[int]:
        st = []
        n = len(nums)

        for i, v in enumerate(nums):
            while (st and st[-1] > v and n + len(st) - i > k):
                st.pop()            
            if len(st) < k: st.append(v)

        return st