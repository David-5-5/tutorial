import heapq

# 面试题
class Solution:
    def getKthMagicNumber(self, k: int) -> int:
        # 堆 + 哈希表
        primes = [3, 5, 7]
        i, h = 1, []
        heapq.heappush(h, 1)
        seen = set()
        while i < k:
            i += 1
            v = heapq.heappop(h)
            for p in primes:
                nxt = v*p
                if nxt not in seen:
                    seen.add(nxt)
                    heapq.heappush(h, nxt)

        return heapq.heappop(h)
    
    def getKthMagicNumber(self, k: int) -> int:
        # 动态规划
        dp = [1] * (k+1)
        p3 = p5 = p7 = 1
        for i in range(2, k+1):
            dp[i] = min(dp[p3]*3, dp[p5]*5, dp[p7]*7)
            
            if dp[i] == dp[p3] * 3: p3 += 1
            if dp[i] == dp[p5] * 5: p5 += 1
            if dp[i] == dp[p7] * 7: p7 += 1
        return dp[k]

