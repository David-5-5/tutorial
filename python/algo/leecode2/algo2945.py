from collections import deque
from itertools import accumulate
from typing import List
class Solution:
    def findMaximumLength(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0] * (n + 1)
        last = [0] * (n + 1)
        # The prefix sum of nums
        pres = [0] * (n + 1)
        for i in range(n):
            pres[i+1] += nums[i] + pres[i]

        # The motonic queues
        mo_que = [0]
        for i in range(1, n+1):
            # pop head of queue, when :
            # 找到符合pres[mo_que[1]] + last[mo_que[1]] <= pres[i] 是满足状态迁移的最大的 j
            while len(mo_que) > 1 and pres[mo_que[1]] + last[mo_que[1]] <= pres[i]:
                mo_que.pop(0)
            
            # 状态迁移
            dp[i] = dp[mo_que[0]] + 1
            last[i] = pres[i] - pres[mo_que[0]]

            # pop tail of queue, when:
            # pres[j] + last[j] >= pres[i+1] + last[i+1]
            while mo_que and pres[mo_que[-1]] + last[mo_que[-1]] >= pres[i] + last[i]:
                mo_que.pop(-1)
            
            mo_que.append(i)
        
        return dp[n]
    
    def findMaximumLength2(self, nums: List[int]) -> int:
        # 2024.10 使用 accumulate deque 等内置方法
        n = len(nums)
        # dp 表示 dp[i] = dp[j] + 1 
        #        last[j] <= last[i] = psum[i+1] - psum[j]
        # 限制条件 j < i, last[i] 尽量小 last[j]+psum[j] 递增
        dp, last= [0] * (n + 1), [0] * (n + 1)
        psum = list(accumulate(nums, initial=0))

        q = deque()

        q.append(0)
        for i in range(1, n+1):
            while len(q) > 1 and last[q[1]] + psum[q[1]] <= psum[i]:
                q.popleft()
            
            dp[i] = dp[q[0]] + 1
            last[i] = psum[i] - psum[q[0]]

            while q and last[q[-1]] + psum[q[-1]] >= psum[i] + last[i]:
                q.pop()
            
            q.append(i)

        return dp[n]
    
    def findMaximumLength3(self, nums: List[int]) -> int:
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

if __name__ == "__main__":
    sol = Solution()
    nums = [279,641,864,511,317,169,848,277]
    
    print(sol.findMaximumLength2(nums))