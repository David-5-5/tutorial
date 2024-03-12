from typing import List
class Solution:
    def minNumberOperations(self, target: List[int]) -> int:
        # 思路 从 target -> initial [0, 0, 0, ..., 0]
        # 遍历每个元素，初始prev为0，
        # a） 当前 val > prev 时， val 变为 0 的在prev次数外，需要增加的操作次数 val - prev
        # b)  当前 val <= prev 时, 表明 val 可以和同一子数组中已经可以变更为 0， 不需要额外的操作
        prev,ans = 0, 0
        for val in target:
            if val > prev:
                ans += val - prev
            prev = val

        return ans
