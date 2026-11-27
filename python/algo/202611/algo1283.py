from bisect import bisect_left


class Solution:
    def smallestDivisor(self, nums: list[int], threshold: int) -> int:
        
        def check(div: int) -> int:
            # if div == 0: return true
            res = 0
            for v in nums:
                res += (v + div - 1) // div
            return res <= threshold
        
        mx = max(nums)
        # l, r = 0, mx + 1
        # while l + 1 < r:
        #     mid = (l + r) // 2
        #     if check(mid):r = mid
        #     else: l = mid
        # return r
        return bisect_left(range(1, mx + 1), True, key=check) + 1