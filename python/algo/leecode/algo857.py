import heapq
class Solution:
    def mincostToHireWorkers(self, quality, wage, k: int) -> float:
        pairs = sorted(zip(quality, wage), key=lambda p: p[1] / p[0])
        ans = 10000000000000000000000
        totalq = 0
        h = []
        for q, w in pairs[:k - 1]:
            totalq += q
            heapq.heappush(h, -q)
        for q, w in pairs[k - 1:]:
            totalq += q
            heapq.heappush(h, -q)
            ans = min(ans, w / q * totalq)
            totalq += heapq.heappop(h)
        return ans

if __name__ == "__main__":
    sol = Solution()
    # quality = [10,20,5]
    # wage = [70,50,30]
    # k = 2
    quality = [3,1,10,10,1]
    wage = [4,8,2,2,7]
    k = 3
    # import random
    # nums = [random.randint(1,20000) for _ in range(1234)]
    # from datetime import datetime
    # begin = datetime.now()
    print(sol.mincostToHireWorkers(quality, wage, k))
    # print((datetime.now()- begin).total_seconds())

