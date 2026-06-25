from typing import List

class Solution:
    def findClosedNumbers(self, num: int) -> List[int]:
        nxt = prev = -1
        low = 0
        for i in range(32):
            if (num >> i) & 1 == 1 and (num >> (i + 1)) & 1 == 0:
                nxt = num + (1 << i)
                nxt -= low
                nxt += (1 << low.bit_count()) - 1
                break
            elif num >> i & 1 == 1: low += 1 << i
        if nxt > 2147483647: nxt = -1

        low = 0
        for i in range(32):
            if num >> i+1 & 1 == 1 and num >> i & 1 == 0:
                prev = num - (1 << i)
                prev -= low
                while low and (low << 1) < (1 << i):
                    low <<= 1
                prev += low
                break
            elif num >> i & 1 == 1: low += 1 << i
        return [nxt, prev]


    def findClosedNumbers2(self, num: int) -> List[int]:
        # 优化
        nxt = prev = -1

        if num == (1 << 31) - 1: return [-1, -1] # 上限

        for i in range(32):
            if (num >> i) & 1 == 1 and (num >> (i + 1)) & 1 == 0:
                # 将 i 位右边的连续 1 右移到末尾
                # 形如：11.0.. 01 1..100000 -> 11.0.. 10 000001..1
                #              i                      i
                suf = num & ((1 << i) - 1)
                nxt = num + (1 << i) + (suf >> (i-suf.bit_count())) - suf
                break

        for i in range(32):
            if num >> i+1 & 1 == 1 and num >> i & 1 == 0:
                # 将 i 位右边的连续 1 左移移到i
                # 形如：11.0.. 10 0..01..1 -> 11.0.. 01 1..10..0
                #              i                     i
                suf = num & ((1 << i) - 1)
                prev = num - (1 << i)  + (suf << (i-suf.bit_count())) - suf
                break

        return [nxt, prev]

