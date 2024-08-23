from collections import defaultdict
from typing import List

# 周赛 316
class Solution:
    def minCost(self, nums: List[int], cost: List[int]) -> int:
        # 自行解答
        dist = defaultdict(int)
        for v, c in zip(nums, cost) : 
            dist[v] += c
        dist[0] = 0
        
        pref, surf = 0, sum(dist.values())
        distnc = sorted([[k,v] for k,v in dist.items()])
        ans = res = sum([k*v for k,v in distnc])
        
        # i,inx = 1, 1
        # while inx < len(distnc): # 枚举 [0，max(nums)]
        #     pref += distnc[inx-1][1]
        #     surf -= distnc[inx-1][1]            
        #     while i <= distnc[inx][0]:
        #         res += pref - surf
        #         ans = min(res, ans)
        #         i += 1
        #     inx += 1
        for inx in range(1, len(distnc)): # 贪心，枚举 nums 列表
            pref += distnc[inx-1][1]
            surf -= distnc[inx-1][1]
            res += (pref-surf) * (distnc[inx][0]- distnc[inx-1][0])
            ans = min(res, ans)

        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, cost = [1,3,5,2], [2,3,1,14]
    print(sol.minCost(nums, cost))