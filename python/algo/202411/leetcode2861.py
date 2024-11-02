from bisect import bisect_left
from typing import List

# 周赛 362
class Solution:
    def maxNumberOfAlloys(self, n: int, k: int, budget: int, composition: List[List[int]], stock: List[int], cost: List[int]) -> int:
        

        # 第 i 台机器制造合金数量
        def check(i:int, cnt:int) -> bool:
            n_bud = 0
            for j in range(n):
                if stock[j] < composition[i][j] * cnt:
                    n_bud += (composition[i][j] * cnt - stock[j]) * cost[j]

            if n_bud <= budget:return True
            else: return False
        
        ans = []
        for i in range(k):
            l, r = -1, budget + min(stock) + 1
            while l + 1 < r:
                mid = (l+r) // 2
                if check(i, mid):
                    l = mid
                else:
                    r = mid
            ans.append(l)
        return max(ans)

if __name__ == "__main__":
    sol = Solution()
    n, k, budget, composition, stock, cost = 3, 2, 15, [[1,1,1],[1,1,10]], [0,0,0], [1,2,3]
    n, k, budget, composition, stock, cost = 2, 3, 10, [[2,1],[1,2],[1,1]], [1,1], [5,5]
    print(sol.maxNumberOfAlloys(n, k, budget, composition, stock, cost))