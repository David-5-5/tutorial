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

