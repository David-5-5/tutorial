from collections import defaultdict
from itertools import accumulate
from typing import Counter, List


class Solution:
    def maxRectangleArea(self, points: List[List[int]]) -> int:
        points.sort(key=lambda p:(p[0],p[1]))
        
        
        p_d = defaultdict(list)
        for x, y in points:
            p_d[x].append(y)
        


        


if __name__ == "__main__":
    sol = Solution()
    nums = [-108,-108,-517]
    print(sol(nums))