from cmath import inf
from collections import defaultdict, deque
from itertools import accumulate
from typing import List


class Solution:
    def findMaximumLength(self, nums: List[int]) -> int:
        n = len(nums)
        q = deque()
        q.append((0,0,0))
        presum = list(accumulate(nums, initial=0))
        for i in range(1, n+1):
            while len(q) > 1 and presum[q[1][2]] + q[1][1] <= presum[i]:
                q.popleft()
            
            cnt ,last = q[0][0]+1, presum[i]-presum[q[0][2]]

            while q and presum[q[-1][2]] + q[-1][1] >= presum[i] + last:
                 q.pop()

            q.append((cnt ,last, i))
        
        return q[-1][0]

if __name__ == '__main__':
    sol = Solution()
    
    nums = [279,641,864,511,317,169,848,277]
    # nums = [5,2,2,2,4,9,10]
    # nums = [1,2,3,4]
    print(sol.findMaximumLength(nums))