from cmath import inf
from itertools import pairwise
from typing import List

# 周赛 294
class Solution:
    def minimumLines(self, stockPrices: List[List[int]]) -> int:
        # 自行解答，避免斜率的精度问题，用前一个x, y的截距代替前一个斜率
        stockPrices.sort()

        prevx = prevy = ans = 0
        for (x1, y1), (x2, y2) in pairwise(stockPrices):
            if ans == 0:
                prevx,  prevy, ans = x2 - x1, y2 - y1, 1
            if prevx * (y2-y1) != prevy * (x2-x1):
                prevx,  prevy= x2 - x1, y2 - y1
                ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
    # stockPrices = [[1,1],[500000000,499999999],[1000000000,999999998]]
    print(sol.minimumLines(stockPrices))
