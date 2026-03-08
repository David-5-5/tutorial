class Solution:
    def findLength(self, nums1, nums2) -> int:
        # 动态规划
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

    def findLength2(self, nums1, nums2) -> int:
        # Sliding window
        ans, n, m = 0, len(nums1), len(nums2)

        def maxLen(inx1: int, inx2: int):
            nonlocal ans
            k = 0
            while inx1<n and inx2<m:
                if nums1[inx1] == nums2[inx2]:
                    k += 1
                else: k = 0
                inx1 += 1
                inx2 += 1
                if k > ans: ans = k
        for i in range(n):
            maxLen(i, 0)
        for j in range(m):
            maxLen(0, j)
        
        return ans