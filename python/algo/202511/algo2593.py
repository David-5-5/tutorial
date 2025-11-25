from typing import List

#滑动窗口与双指针 - 六、分组循环
class Solution:
    def findScore(self, nums: List[int]) -> int:
        # 自行解答
        ans, n = 0, len(nums)
        marked = [0] * n
        
        # 用 python 比 c++ 容易实现多了
        # 两种写法
        # for i, v in sorted(enumerate(nums), key=lambda p:p[1]):
        for v, i in sorted(zip(nums, range(n))):
            if (marked[i]): continue
            ans += v
            marked[i] = 1
            if i: marked[i-1] = 1
            if i+1 < n: marked[i+1] = 1
        return ans