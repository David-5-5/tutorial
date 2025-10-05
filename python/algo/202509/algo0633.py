from math import isqrt

# 数学算法 - 数论 - 1.10 其他
class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        a = 0
        while a * a * 2 <= c:
            b = isqrt(c-a*a) # int(sqrt(c-a*a))
            if b * b + a * a == c:
                return True
            a += 1

        return False

    def judgeSquareSum2(self, c: int) -> bool:
        mx = isqrt(c)
        nums = [i*i for i in range(mx+1)]
        l , r = 0, len(nums) - 1
        while l <= r: # a == b
            if nums[l] + nums[r] == c: return True
            elif nums[l] + nums[r] > c: r -= 1
            else: l += 1
        return False