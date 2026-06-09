from cmath import inf
from typing import List

# 贪心 八、其他
class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        # land -> water
        mn_fin_land = inf
        for s, d in zip(landStartTime, landDuration):
            mn_fin_land = min(mn_fin_land, s + d)
        
        res = inf
        for s, d in zip(waterStartTime, waterDuration):
            res = min(res, max(mn_fin_land, s) + d)

        # water -> land
        mn_fin_water = inf
        for s, d in zip(waterStartTime, waterDuration):
            mn_fin_water = min(mn_fin_water, s + d)
        
        for s, d in zip(landStartTime, landDuration):
            res = min(res, max(mn_fin_water, s) + d)

        return res