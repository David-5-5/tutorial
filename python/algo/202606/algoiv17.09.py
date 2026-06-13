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
    
