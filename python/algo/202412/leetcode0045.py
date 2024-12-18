from typing import List

# 贪心专题 - 区间覆盖
class Solution:
    def jump(self, nums: List[int]) -> int:
        # 参考 1326 区间覆盖 模板
        n = len(nums)
        right_most = [0] * (n)
        for i, r in enumerate(nums):
            right_most[i] = max(right_most[i], i + r) # max(n-1, i+r)

        ans = 0
        cur_right = 0  # 已建造的桥的右端点
        next_right = 0  # 下一座桥的右端点的最大值
        for i in range(n):  # 如果走到 n-1 时没有返回 -1，那么必然可以到达 n
            if cur_right >= n-1 : break
            next_right = max(next_right, right_most[i])
            if i == cur_right:  # 到达已建造的桥的右端点
                cur_right = next_right  # 造一座桥
                ans += 1

        return ans

    