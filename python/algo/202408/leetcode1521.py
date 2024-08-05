from math import inf
from typing import List


class Solution:
    def closestToTarget(self, arr: List[int], target: int) -> int:

        ans = set()
        ands = set()
        for x in arr:
            ands = { o & x for o in ands}
            ands.add(x)
            ans |= ands


        mn = inf
        for x in ans:
            if abs(x - target) < mn:
                mn = abs(x - target)
        return mn
    
if __name__ == "__main__":
    sol = Solution()
    arr, ta = [9,12,3,7,15], 5
    print(sol.closestToTarget(arr, ta))