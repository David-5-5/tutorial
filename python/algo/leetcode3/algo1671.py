from bisect import bisect_left
from functools import lru_cache
from typing import List
class Solution:
    def minimumMountainRemovals(self, nums: List[int]) -> int:
        # 求出最大递增子序列长度及最大递减子序列长度
        # max(n+1 - 每个元素的最大递增子序列及递减子序列的和) 
        # 同时需要山形数组，因此符合条件的元素的递减子序列及递增子序列同时大于1 

        n = len(nums)
        incr = [0] * n
        degr = [0] * n
        
        dpi = []
        dpd = []
        for i in range(n):
            inx1 = bisect_left(dpi, nums[i])
            if (inx1) < len(dpi):
                dpi[inx1] = min(dpi[inx1], nums[i])
                incr[i] = inx1 + 1
            else:
                dpi.append(nums[i])
                incr[i] = len(dpi)
            
            inx2 = bisect_left(dpd, nums[n-1-i])
            if (inx2) < len(dpd):
                dpd[inx2] = min(dpd[inx2], nums[n-1-i])
                degr[i] = inx2 + 1
            else:
                dpd.append(nums[n-1-i])
                degr[i] = len(dpd)
            

        return n + 1 - max([a+b if a>1 and b>1 else 0 for a, b in zip(incr, reversed(degr))])

    def minimumMountainRemovals2(self, nums: List[int]) -> int:
        
        # 提出公共方法 复用 300 LIS
        def lengthOfLIS3(nums: List[int]) -> List[int]:
            '''The final solution, time complex is O(NlogN)
            '''
            n = len(nums)
            # dp 固定最小连续序列的长度，其值为该序列长度的最小值。索引从0开始，长度序列从1开始，因此长度=索引+1
            # 最后返回的结果为len(dp)
            dp = []
            ans = [0] * n
            for i in range(n):
                inx = bisect_left(dp, nums[i])
                if (inx) < len(dp):
                    dp[inx] = min(dp[inx], nums[i])
                    ans[i] = inx + 1
                else:
                    dp.append(nums[i])
                    ans[i] = len(dp)
            return ans
        
        incr = lengthOfLIS3(nums)
        degr = lengthOfLIS3(nums[::-1])[::-1]

        return len(nums) + 1 - max([a+b if a>1 and b>1 else 0 for a, b in zip(incr, degr)])
    
if __name__ == "__main__":
    sol = Solution()
    nums = [9,8,1,7,6,5,4,3,2,1]
    print(sol.minimumMountainRemovals(nums))
    print(sol.minimumMountainRemovals2(nums))