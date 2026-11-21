import heapq


class Solution:
    def nthSuperUglyNumber(self, n: int, primes: list[int]) -> int:
        pq, vis = [1], set()
        heapq.heapify(pq)

        for _ in range(n-1):
            mn = heapq.heappop(pq)
            for v in primes:
                if v * mn in vis: continue
                vis.add(v * mn)
                heapq.heappush(pq, v * mn)

        return heapq.heappop(pq)

    def nthSuperUglyNumber2(self, n: int, primes: list[int]) -> int:
        m = len(primes)
        idx = [0] * m

        dp = [1] * n
        for i in range(1, n):
            mn = min([dp[idx[j]] * primes[j] for j in range(m)])
            for j in range(m):
                if dp[idx[j]] * primes[j] == mn:
                    idx[j] += 1
            dp[i] = mn
        return dp[-1]