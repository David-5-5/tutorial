import heapq
from typing import List

# 专题：优先队列
class Solution:
    def isPossible(self, target: List[int]) -> bool:
        if len(target) == 1: return target == 1
        n_sum = sum(target)
        
        neg = [-v for v in target]
        heapq.heapify(neg)
        while neg[0] != -1:
            maxv = - heapq.heappop(neg)
            if 2 * maxv - n_sum < 1: return False
            left = n_sum - maxv
            y =  - neg[0]
            if y == 1: k = (maxv-y+left-1) // left
            else: k = (maxv-y)//left + 1
            next = maxv - k * left
            if next <=0: return False
            n_sum -= k * left
            heapq.heappush(neg, -next)

        return True
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.isPossible([1,1000000000]))