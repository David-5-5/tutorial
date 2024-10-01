from math import gcd
from typing import Counter, List

# 周赛 342
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        # 自行解答
        # 情况 1,所有数的最大公因数不等于 1, 无法完成
        if gcd(*nums) != 1: return -1

        # 情况2, nums中存在 1,则仅需要从 1 开始 将非 1 数置为 1 即可
        cnt = Counter(nums)
        if cnt[1]: return len(nums) - cnt[1]
        
        # 情况3, 结果初始化为 nums 长度
        # 两两求公因数，每次循环不出现 公因数 1, 则结果 +1
        #                     出现 公因数 1, 则返回结果
        ans = len(nums)
        cur, next =nums.copy(), []
        while cur:
            for i in range(len(nums)-1):
                g = gcd(cur[i], cur[i+1])
                if g == 1:
                    return ans
                next.append(g)
            next.append(g)
            cur, next = next, []
            ans += 1


                
            