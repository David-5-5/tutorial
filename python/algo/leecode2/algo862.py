from typing import List
from bisect import bisect_right
from itertools import accumulate
from collections import deque
class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = float("inf")
        # 前缀和
        presum = [0] * n
        for i in range(n):
            presum[i] = nums[i] + (presum[i-1] if i else 0)
        
        # monotonic queue
        # (presum[i] + k, i), 其中
        # 1) i 索引递增， 
        # 2) 同时满足 presum[j] + k < presum[i] + k, 
        #    因此将队列尾部 presum[j] + k >= presum[i] + k的元素出队列 j < i
        queue = []
        for i in range(n+1):
            if presum[i] >= k:
                ans = min(ans, i+1)
            inx = bisect_right(queue, (presum[i], i))
            
            if inx > 0 and queue[inx-1][0] <= presum[i]:
                ans = min(ans, i-queue[inx-1][1])

            # 将队列尾部presum[j] + k >= presum[i] + k的元素出队列, 对于presum[j] + k >= presum[i] + k的元素且j < i,
            # j 和 i 相比较没有任何优势 ，要么其和 nums[j..t] 不大于 nums[i..t]，(注: presum[t]-presum[j] = nums[i..t])
            # 且从 j 开始数组长度大于从 i 开始的数组
            while queue and queue[-1][0] >= presum[i] + k:
                queue.pop(-1)
            queue.append((presum[i] + k, i))

            if ans == 1:return ans

        return -1 if ans == float("inf") else ans

    def shortestSubarray2(self, nums: List[int], k: int) -> int:
        '''shortestSubarray2 compare to shortestSubarray2
        LIST compare to DEQUE
        进一步优化, presum是递增的(nums大于零)
        '''
        n = len(nums)
        ans = float("inf")
        # 前缀和
        presum = list(accumulate(nums, initial=0))  # 计算前缀和
        
        # monotonic queue 
        queue = []
        for i in range(n+1):
            while queue and presum[i] - presum[queue[0]] >= k:
                ans = min(ans, i - queue.pop(-1))

            while queue and presum[queue[-1]] >= presum[i]:
                queue.pop()
            queue.append(i)

            if ans == 1:return ans

        return -1 if ans == float("inf") else ans

    def shortestSubarray3(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = float("inf")
        # 前缀和
        presum = list(accumulate(nums, initial=0))  # 计算前缀和
        
        # monotonic queue 
        queue = deque()
        for i in range(n+1):
            while queue and presum[i] - presum[queue[0]] >= k:
                ans = min(ans, i - queue.popleft())

            while queue and presum[queue[-1]] >= presum[i]:
                queue.pop()
            queue.append(i)

            if ans == 1:return ans

        return -1 if ans == float("inf") else ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1], 1
    # nums, k = [-28,81,-20,28,-29], 89
    print(sol.shortestSubarray(nums, k))
    print(sol.shortestSubarray2(nums, k))
    print(sol.shortestSubarray3(nums, k))