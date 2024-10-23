from bisect import bisect_left
import math

# 双周赛 94
class Solution:
    def minimizeSet(self, divisor1: int, divisor2: int, uniqueCnt1: int, uniqueCnt2: int) -> int:
        # 参考题解
        lcm = math.lcm(divisor1, divisor2)

        def check(mx:int) -> bool:
            # mx // divisor2 - mx // lcm 表明仅能被 arr1 选择的数字
            # left1 表明是剩下  uniqueCnt1 - (mx // divisor2 - mx // lcm)，
            #       后续在两组数字共享的数字中选择 (arr2 同样处理)
            left1 = max(0, uniqueCnt1 - (mx // divisor2 - mx // lcm)) 
            left2 = max(0, uniqueCnt2- (mx // divisor1 - mx // lcm))
            # common 表示是arr1 和 arr2 共享的数据
            common = mx - (mx // divisor1 + mx // divisor2 - mx // lcm)
            return  common >= left1 + left2
            
        right = (uniqueCnt1 + uniqueCnt2) * 2
        
        return bisect_left(range(right), True, key=check)


if __name__ == "__main__":
    sol = Solution()
    print(sol.minimizeSet(2, 4, 8, 2))