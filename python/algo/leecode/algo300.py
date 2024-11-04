from functools import cache
from typing import List
from bisect import bisect_left, bisect_right
class Solution:
    def lengthOfLIS(self, nums) -> int:
        '''未优化的方案, 时间复杂度O(N^2)
        '''
        n = len(nums)
        # maxLen = 1
        # maxNum = -10000
        dp = [1] * n
        for i in range(n-1, -1, -1):
            # if nums[i] > maxNum:
            #     maxNum = nums[i]
            for j in range(i+1, n):
            #     if nums[j] > maxNum:
            #         break
                if nums[i] < nums[j]:
                    dp[i] = max(dp[i], dp[j]+1)
        return max(dp)

    
    def lengthOfLIS2(self, nums: List[int]) -> int:
        '''The solution with error, although it could pass throught
        '''
        n = len(nums)
        # The sequenc len which i is the last
        dp = [1] * n
        # Create the montic queue of of nums[i], the element is tuple
        # Fisrt is nums[i]
        # Second is the maximums lenght suqence which the nums[i] last
        q = []
        for i in range(n):
            if not q:
                q.append((nums[i], dp[i]))
            else:
                inx = bisect_left(q, (nums[i],dp[i]))
                if inx > 0:
                    dp[i] += q[inx-1][1]
                
                if inx < len(q) and q[inx][0] == nums[i]:
                    q[inx] = (nums[i], dp[i])
                else:
                    if inx < len(q) and dp[i]-nums[i] <= q[inx][1]-q[inx][0]:
                        continue
                    q.insert(inx, (nums[i], dp[i]))

                if inx-1 > 0 and q[inx-1][1]-q[inx-1][0]<= q[inx][1]-q[inx][0]:
                    del q[inx-1]
                                
                # If len of the sequent large num is less than inx of q, delete it 
                ql = len(q)
                for i in range(ql-1, inx, -1):
                    if q[i][1] <= q[inx][1]:
                        del q[i]
                

        return max(dp) 



    def lengthOfLIS3(self, nums: List[int]) -> int:
        '''The final solution, time complex is O(NlogN)
        '''
        n = len(nums)
        # dp 固定最小连续序列的长度，其值为该序列长度的最小值。索引从0开始，长度序列从1开始，因此长度=索引+1
        # 最后返回的结果为len(dp)
        dp = []

        for i in range(n):
            inx = bisect_left(dp, nums[i])
            if (inx) < len(dp):
                dp[inx] = min(dp[inx], nums[i])
            else:
                dp.append(nums[i])

        return len(dp)

    def lengthOfLIS3(self, nums: List[int]) -> int:
        '''The final solution, time complex is O(NlogN)
        '''
        n = len(nums)
        # dp 固定最小连续序列的长度，其值为该序列长度的最小值。索引从0开始，长度序列从1开始，因此长度=索引+1
        # 最后返回的结果为len(dp)
        dp = []

        for i in range(n):
            inx = bisect_left(dp, nums[i])
            if (inx) < len(dp):
                dp[inx] = min(dp[inx], nums[i])
            else:
                dp.append(nums[i])

        return len(dp)

    def lengthOfLIS4(self, nums: List[int]) -> int:
        # 优化前的标准实现，放在这里比较，更加深刻的理解动态规划的优化
        # 最最重要的是优化的思路，分析问题和解决问题的能力
        @cache
        def dfs(i:int) -> int:
            if i == 0: return 1
            
            res = 1
            for j in range(i):
                if nums[j] < nums[i] : res = max(res, dfs(j)+1)
            return res
        return max(dfs(i) for i in range(len(nums)))
    
if __name__ == "__main__":
    sol = Solution()
    nums = [10,9,2,5,3,7,101,18]
    print(sol.lengthOfLIS3(nums))
    print(sol.lengthOfLIS4(nums))
