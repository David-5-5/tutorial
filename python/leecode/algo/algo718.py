class Solution:
    def findLength(self, nums1, nums2) -> int:
        n = len(nums1)
        m = len(nums2)

        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

        for i in range(n):
            for j in range(m):
                if nums1[i] == nums2[j]:
                    dp[i+1][j+1] = dp[i][j] + 1
                else:
                    dp[i+1][j+1]
        return max(max(row) for row in dp)
