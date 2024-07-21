from bisect import bisect_left
from itertools import accumulate
from typing import List

class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        n = len(stations)
        presum = list(accumulate(stations, initial=0))
        st = [0] * n

        for i in range(n):
            st[i] = presum[min(n,i+r+1)] - presum[max(0, i-r)]
        
        # Use bi search by self
        # def check(min_power:int) -> bool:
        #     diff = [0] * n
        #     sum_d = need = 0
        #     for i, power in enumerate(st):
        #         sum_d += diff[i]
        #         delta = min_power - power - sum_d
        #         if delta > 0:
        #             need += delta
        #             if need > k: return False
        #             sum_d += delta # diff[i] += delta
        #             if i + 2*r + 1 < n:
        #                 diff[i + 2*r + 1] -= delta
        #     return True

        # left, right = -1, presum[n] + k + 1
        # while left + 1 < right:
        #     mid = (left + right) // 2
        #     if check(mid): left = mid
        #     else: right = mid
        # return left

        # Use bisect_left
        def check(min_power:int) -> bool:
            min_power += 1 # Left true, right False
            diff = [0] * n
            sum_d = need = 0
            for i, power in enumerate(st):
                sum_d += diff[i]
                delta = min_power - power - sum_d
                if delta > 0:
                    need += delta
                    if need > k: return True
                    sum_d += delta # diff[i] += delta
                    if i + 2*r + 1 < n:
                        diff[i + 2*r + 1] -= delta
            return False

        return bisect_left(range(presum[n] + k), True, key=check)      

if __name__ == "__main__":
    sol = Solution()
    stations, r, k = [1,2,4,5,0], 1, 2
    print(sol.maxPower(stations, r, k))