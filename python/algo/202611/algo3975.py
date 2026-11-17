from typing import List


class Solution:
    def filterOccupiedIntervals(self, occupiedIntervals: List[List[int]], freeStart: int, freeEnd: int) -> List[List[int]]:
        occupiedIntervals.sort()

        cand, ans = [], []
        for l, r in occupiedIntervals:
            if len(cand) == 0 or cand[-1][1]+1 < l:
                cand.append([l, r])
            elif cand[-1][1] < r:
                cand[-1][1] = r
        
        for l, r in cand:
            if l > freeEnd or r < freeStart: ans.append([l, r])
            else:
                if l <= freeStart-1 <= r: ans.append([l, freeStart-1])
                if l <= freeEnd + 1 <= r: ans.append([freeEnd+1, r])
        
        return ans