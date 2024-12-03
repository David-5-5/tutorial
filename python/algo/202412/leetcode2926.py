from math import inf
from typing import List

from sortedcontainers import SortedList

# 周赛 370
class Solution:
    def maxBalancedSubsequenceSum(self, nums: List[int]) -> int:
        # 自行解答(标题方案) 
        # 计算 nums[i_j] - i_j 的值，并离散化
        mono = set()
        for i, v in enumerate(nums):
            if v <= 0 :continue
            mono.add(v-i)
        
        mono = SortedList(mono) # 值对应的下标即为离散化的值
        n = len(mono)

        if n == 0: return max(nums) # 都是非正数，返回最大的值

        dp = [0] * (4 * n)
    
        # 线段数 - 模板 - 区间最大值
        def update(inx:int, val:int, s:int, t:int, p:int):
            # [l, r] 为修改区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if inx == s and inx == t:
                dp[p] = val
                return
            # 当前区间为修改区间的子集时直接修改当前节点的值, 然后打标记, 结束修改
            m = s + ((t - s) >> 1)
            if inx <= m:
                update(inx, val, s, m, p*2+1)
            if inx > m:
                update(inx, val, m + 1, t, p*2+2)
            
            dp[p] = max(dp[p*2+1], dp[p*2+2])

        def query(l, r, s, t, p):
            # [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                return dp[p]
            # 当前区间为询问区间的子集时直接返回当前区间的和
            m = s + ((t - s) >> 1)
            maxv = 0
            if l <= m:
                maxv = query(l, r, s, m, p * 2 + 1)
            if r > m:
                maxv = max(maxv, query(l, r, m + 1, t, p * 2 + 2))
            return maxv
        ##

        ans = 0
        for i, v in enumerate(nums):
            if v <=0: continue
            r = mono.bisect_left(v-i)

            maxs = query(0, r, 0, n-1, 0)
            update(r, maxs+v, 0, n-1, 0)
            ans = max(ans, maxs+v)
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [3,3,5,6]
    print(sol.maxBalancedSubsequenceSum(nums))