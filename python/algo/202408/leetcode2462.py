from cmath import inf
from heapq import heapify, heapreplace, heappop
from typing import List

# 周赛 318
class Solution:
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:
        n = len(costs)
        if candidates * 2 > n:
            costs.sort()
            return sum(costs[:k])
        
        pre = costs[:candidates] + [inf]
        suf = costs[n-candidates:]  + [inf]
        heapify(pre), heapify(suf)
        # i, j 在 pre 和 suf 中， 因此先 +/- 后取， 
        i, j = candidates-1, n - candidates

        res = 0
        while k:
            if pre[0] <= suf[0]:
                if i + 1 < j:
                    res += heapreplace(pre, costs[i+1])
                    i += 1
                else:
                    res += heappop(pre)
            else:
                if j-1 > i:
                    res += heapreplace(suf, costs[j-1])
                    j -= 1
                else:
                    res += heappop(suf)
            k -= 1
        return res

    def totalCost2(self, costs: List[int], k: int, candidates: int) -> int:
        # 简化 totalCost
        res = 0
        if candidates * 2 + k < len(costs):
            pre = costs[:candidates]
            suf = costs[len(costs)-candidates:]
            heapify(pre), heapify(suf)
            # i, j 在 pre 和 suf 中， 因此先 +/- 后取， 
            i, j = candidates-1, len(costs) - candidates

            while k and i+1 < j:
                if pre[0] <= suf[0]:
                    res += heapreplace(pre, costs[i+1])
                    i += 1
                else:
                    res += heapreplace(suf, costs[j-1])
                    j -= 1
                k -= 1
            costs = pre + suf
        costs.sort()
        return res + sum(costs[:k])

    def totalCost3(self, costs: List[int], k: int, candidates: int) -> int:
        # 参考题解
        if candidates * 2 + k > len(costs): # 关键点1 区别totalCost2
            costs.sort()
            return sum(costs[:k])            

        res = 0

        pre = costs[:candidates]
        suf = costs[len(costs)-candidates:]
        heapify(pre), heapify(suf)
        # i, j 在 pre 和 suf 中， 因此先 +/- 后取， 
        i, j = candidates-1, len(costs) - candidates

        while k :  # 关键点2 区别totalCost2
            if pre[0] <= suf[0]:
                res += heapreplace(pre, costs[i+1])
                i += 1
            else:
                res += heapreplace(suf, costs[j-1])
                j -= 1
            k -= 1

        return res 

if __name__ == "__main__":
    sol = Solution()
    costs, k, candidates = [17,12,10,2,7,2,11,20,8], 3, 4
    costs, k, candidates = [31,25,72,79,74,65,84,91,18,59,27,9,81,33,17,58], 11, 2
    print(sol.totalCost(costs, k, candidates))
    print(sol.totalCost3(costs, k, candidates))