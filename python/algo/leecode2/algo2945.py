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

if __name__ == "__main__":
    sol = Solution()
    nums = [418,421,309,442,80,305,166,884,791,353]
    print(sol.findMaximumLength(nums))