from typing import List
from bisect import bisect_left
class Solution:
    def lengthOfLIS(self, nums) -> int:
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
                    q.insert(inx, (nums[i], dp[i]))
                ql = len(q)
                # If len of the sequent large num is less than inx of q, delete it 
                for i in range(ql-1, inx, -1):
                    if q[i][1] <= q[inx][1]:
                        del q[i]

        return max(dp) 

if __name__ == "__main__":
    sol = Solution()
    nums = [10,9,2,5,3,7,101,18]
    print(sol.lengthOfLIS2(nums))

    # performance compare with lengthOfLIS and lengthOfLIS
    import random
    from datetime import datetime
    nums = [random.randint(-100000, 100000) for _ in  range(12500)]
    begin = datetime.now()
    print(sol.lengthOfLIS(nums))
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    print(sol.lengthOfLIS2(nums))
    print((datetime.now()- begin).total_seconds())