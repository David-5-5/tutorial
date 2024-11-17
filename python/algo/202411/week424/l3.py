from bisect import bisect_left
from itertools import accumulate
from typing import List


class Solution:
    def isZeroArray(self, nums: List[int], queries: List[List[int]]) -> bool:
        # 自行解答 差分数组 + 二分
        n, m = len(queries), len(nums)
        def check(k:int):
            diff = [0] * m
            for l, r, v in queries[0:k]:
                diff[l] += v
                if r + 1 < m: diff[r+1] -= v
            pres = list(accumulate(diff))
            return all(ori<=qu for ori, qu in zip(nums, pres))

        ans = bisect_left(range(n+1), True, key=check)        
        return ans if ans < n+1 else -1
    
if __name__ == "__main__":
    sol = Solution()
    nums, queries = [10], [[0,0,5],[0,0,3],[0,0,2],[0,0,1],[0,0,4],[0,0,1],[0,0,4],[0,0,5],[0,0,3],[0,0,4],[0,0,1]]
    print(sol.isZeroArray(nums,queries))