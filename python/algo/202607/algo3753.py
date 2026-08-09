from functools import cache
from typing import Tuple


class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        # 自行解答，数位 DP
        def cmp (a:int, b: int) ->int:
            if a < b: return 1
            elif a == b:  return 0
            else: return -1

        upper = str(num2)
        lower = str(num1).rjust(len(upper), '0')
        n = len(upper)

        @cache
        def f(i: int, state: int, prev:int, isNum:bool, lowLimit: bool, upLimit: bool) -> Tuple[int, int]:
            if i == n: return (0, 1)

            # pv_cnt: count of peak and valley, tot: total count
            pv_cnt, tot = 0, 0
            lo = int(lower[i]) if lowLimit else 0
            up = int(upper[i]) if upLimit else 9
            for d in range(lo, up+1):
                pv = 0
                if isNum and prev != -1 and state != 0 and cmp(prev, d) != 0:
                    pv = (state != cmp(prev, d))
                p_pv_cnt, p_tot = f(i+1, cmp(prev, d) if isNum and prev!=-1 else 0, d, isNum or d>0, lowLimit and d == lo, upLimit and d == up)
                # 关键 pv * 后续遍历到的整数的数量
                pv_cnt += pv * p_tot + p_pv_cnt
                tot += p_tot

            return (pv_cnt, tot)
        
        return f(0, 0, -1, False, True, True)[0]


if __name__ == "__main__":
    print(Solution().totalWaviness2(98, 100))
