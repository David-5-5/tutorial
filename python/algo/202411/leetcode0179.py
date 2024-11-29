from functools import cmp_to_key
from typing import List

# 贪心专题 交换论证法
class Solution:
    def largestNumber(self, nums: List[int]) -> str:
        def func(x, y):
            sx = sy = 10
            while sx <= x: sx *= 10
            while sy <= y: sy *= 10
            return 1 if sx * y + x > sy * x + y else -1

        ans = "".join(str(v) for v in sorted(nums, key=cmp_to_key(func)))
        return ans if ans[0] != '0' else '0'

    def largestNumber2(self, nums: List[int]) -> str:
        def func(x, y):
            return 1 if x+y < y+x else -1
        
        # Correct 1
        # st = sorted([str(v) for v in nums], key=cmp_to_key(func))
        # ans = "".join(st)
            
        ans = "".join(sorted([str(v) for v in nums], key=cmp_to_key(func)))
        return ans if ans[0] != '0' else '0'

if __name__ == "__main__":
    sol = Solution()
    print(sol.largestNumber2([3,30,34,5,9]))