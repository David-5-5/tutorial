from typing import List


class Solution:
    def minimumOR(self, grid: List[List[int]]) -> int:
        # OR 的最小值，按从高位选择到低位 套路 [按位选择]
        mx = max(v for r in grid for v in r)
        l = mx.bit_length()

        mask, ans = 0, 0
        for i in range(l-1, -1, -1):
            cur, found = 1<<i,  False
            for row in grid:
                if all(v & cur for v in row if v & mask & ~ans == 0):
                    found = True
                    break
            mask |= cur
            if found: ans |= cur
        return ans



if __name__ == "__main__":
    Solution().minimumOR([[1,5],[2,4]])

