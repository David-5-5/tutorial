from typing import List

# 贪心 八、其他
class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        # 自行解答
        odd, even, n = [], [], len(nums)
        for i, v in enumerate(nums):
            if v % 2: odd.append(i)
            else: even.append(i)
        
        if abs(len(odd) - len(even)) > 1: return -1

        def arrange(arr: List[int]) -> int:
            res = 0
            for i in range(0, n, 2):
                res += abs(arr[i//2] - i)
            return res


        if len(odd) == len(even): return min(arrange(odd), arrange(even))
        elif len(odd) > len(even): return arrange(odd)
        else: return  arrange(even)   