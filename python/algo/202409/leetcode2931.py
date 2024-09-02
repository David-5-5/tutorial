import heapq
from typing import List

# 双周赛 117
class Solution:
    def maxSpending(self, values: List[List[int]]) -> int:
        m, n = len(values), len(values[0])
        pr = []
        # 初始化
        for i in range(m):
            heapq.heappush(pr, (values[i][-1], i, n-1))

        ans = d = 0
        while pr:
            d += 1
            val, i, j = heapq.heappop(pr)
            ans += val * d
            if j > 0: heapq.heappush(pr, (values[i][j-1], i, j-1))
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    values = [[8,5,2],[6,4,1],[9,7,3]]
    print(sol.maxSpending(values))