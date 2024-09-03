from collections import defaultdict
from typing import List

# 周赛 308
class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        ans = 0
        last = defaultdict(int)
        for i, g in enumerate(garbage):
            ans += len(g)
            for c in g:
                last[c] = i
        for r in last.values():
            ans += sum(travel[:r])
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    garbage, travel = ["G","P","GP","GG"], [2,4,3]
    print(sol.garbageCollection(garbage, travel))