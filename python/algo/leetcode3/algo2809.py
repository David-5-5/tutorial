from typing import List
class Solution:
    def minimumTime(self, nums1: List[int], nums2: List[int], x: int) -> int:
        n = len(nums1)

        dp = [[0] * (n + 1) for _ in range(n + 1)]
        s1, s2 = sum(nums1), sum(nums2)

        nums = sorted(zip(nums1,nums2),key=lambda z:z[1])
        
        for i in range(n):
            for j in range(1,n+1):
                dp[i+1][j] = max(dp[i][j], dp[i][j-1] + nums[i][0] + j * nums[i][1] )
        
        for i in range(n+1):
            if s1 + s2 * i - dp[n][i] <= x:
                return i
        return -1
    
    def minimumTime2(self, nums1: List[int], nums2: List[int], x: int) -> int:
        n = len(nums1)

        dp = [0] * (n + 1)
        s1, s2 = sum(nums1), sum(nums2)

        # for a, b in zip(nums1,nums2):
        for a, b in sorted(zip(nums1,nums2),key=lambda z:z[1]):
            for j in range(n, 0, -1):
                dp[j] = max(dp[j], dp[j-1] + a + j * b)
        
        for i in range(n+1):
            if s1 + s2 * i - dp[i] <= x:
                return i
        return -1

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, x = [2,1,3], [2,1,3], 4
    print(sol.minimumTime2(nums1, nums2, x))