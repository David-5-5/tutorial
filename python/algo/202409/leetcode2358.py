
from bisect import bisect_right
import math
from typing import List

# 周赛 304
MAX = 10 ** 5

q = []
i = 1
while i*(i+1) // 2 <= MAX:
    q.append(i*(i+1) // 2)
    i += 1

class Solution:
    def maximumGroups(self, grades: List[int]) -> int:
        n = len(grades)
        inx = bisect_right(q, n)
        return inx
    
    def maximumGroups2(self, grades: List[int]) -> int:
        return math.floor((math.sqrt(8*len(grades)+1)-1)/2)

if __name__ == "__main__":
    sol = Solution()
    grades = [10,6,12,7,3,5]
    print(sol.maximumGroups(grades))
    print(sol.maximumGroups2(grades))