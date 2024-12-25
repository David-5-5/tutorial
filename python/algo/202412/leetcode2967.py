from bisect import bisect_left, bisect_right
from itertools import accumulate
from math import inf
from typing import List

from sortedcontainers import SortedList
# 预先 生成回文数 模板
pal = []
base = 1
while base <= 10000:
    # 生成奇数长度回文数
    for i in range(base, base * 10):
        x = i
        t = i // 10
        while t:
            x = x * 10 + t % 10
            t //= 10
        pal.append(x)
    # 生成偶数长度回文数
    if base <= 1000:
        for i in range(base, base * 10):
            x = t = i
            while t:
                x = x * 10 + t % 10
                t //= 10
            pal.append(x)
    base *= 10
pal.append(1_000_000_001)  # 哨兵，防止下面代码中的 i 下标越界

# 周赛 376
class Solution:
    def minimumCost(self, nums: List[int]) -> int:
        n = len(nums)
        nums = SortedList(nums)
        pres = list(accumulate(nums, initial =0))
        mn, mx = nums[0], nums[-1]

        begin = max(bisect_left(pal, mn)-1,0)
        end = bisect_right(pal, mx)
        ans = inf
        for i in range(begin, end+1):
            inx = nums.bisect_left(pal[i])
            val =  pal[i] * (2 * inx - n) - 2 * pres[inx] + pres[n]
            if val < ans:
                ans = val

        return ans 
    

if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumCost([56]))