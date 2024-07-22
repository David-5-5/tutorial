from bisect import bisect_left
import math


class Solution:
    def minimizeSet(self, divisor1: int, divisor2: int, uniqueCnt1: int, uniqueCnt2: int) -> int:
        lcm = math.lcm(divisor1, divisor2)

        def check(mx:int) -> bool:
            left1 = max(0, uniqueCnt1 - (mx // divisor2 - mx // lcm))
            left2 = max(0, uniqueCnt2- (mx // divisor1 - mx // lcm))
            common = mx - (mx // divisor1 + mx // divisor2 - mx // lcm)
            return  common >= left1 + left2
            
        right = (uniqueCnt1 + uniqueCnt2) * 2
        
        return bisect_left(range(right), True, key=check)


if __name__ == "__main__":
    sol = Solution()
    print(sol.minimizeSet(2, 4, 8, 2))