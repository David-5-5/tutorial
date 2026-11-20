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

