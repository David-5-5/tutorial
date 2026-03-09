from bisect import bisect_left


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

    def findLength3(self, nums1, nums2) -> int:
        # rabinKarp + binary search
        n, m = len(nums1), len(nums2)

        base = 113
        mod = 10 ** 9 + 9

        def check(lenght: int):
            if lenght == 0: return True
            blen = pow(base, lenght-1, mod)
            bucket = set()  # for hash1
            hash1, hash2 = 0, 0
            for i in range(lenght):
                hash1 = (hash1 * base + nums1[i]) % mod
                hash2 = (hash2 * base + nums2[i]) % mod
            
            if hash1 == hash2: return True
            bucket.add(hash1)
            for i in range(lenght, n):
                hash1 = ((hash1 - nums1[i-lenght]*blen) * base  + nums1[i]) % mod
                bucket.add(hash1)
            
            if hash2 in bucket: return True
            for i in range(lenght, m):
                hash2 = ((hash2 - nums2[i-lenght]*blen) * base  + nums2[i]) % mod
                if hash2 in bucket: return True
            
            return False

        left , right = -1, min(n, m) + 1
        while left + 1 < right:
            mid = (left + right) // 2
            if check(mid): left = mid
            else: right = mid
        return left