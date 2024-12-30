from typing import List

# 双周赛 139
class Solution:
    def maxValue(self, nums: List[int], k: int) -> int:
        n = len(nums)
        pre = [[[False] * (2**7) for _ in range(k+1)] for _ in range(n-k+1)]
        suf = [[[False] * (2**7) for _ in range(k+1)] for _ in range(n-k+1)]
        pre[0][0][0] = suf[0][0][0] = True

        for i in range(n-k):
            for j in range(k):
                for x in range(2**7):
                    if pre[i][j][x]:
                        pre[i+1][j][x] = pre[i][j][x] # 不选 nums[i]
                        pre[i+1][j+1][x|nums[i]] = pre[i][j][x]    # 选 nums[n-i-1]
                    if suf[i][j][x]:
                        suf[i+1][j][x] = suf[i][j][x] # 不选 nums[n-i-1]
                        suf[i+1][j+1][x|nums[n-i-1]] = suf[i][j][x] # 选 nums[n-i-1]
        
        ans = 0
        for i in range(k, n-k+1):
            for x in range(2**7):
                for y in range(2**7):
                    if pre[i][k][x] and suf[n-i+1][k][y]:
                        ans = max(ans, x^y)
        return ans