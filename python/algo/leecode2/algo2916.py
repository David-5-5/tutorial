from typing import List
import math

# 双周赛 116 线段数 懒更新 lazy update
class Solution:
    def sumCounts(self, nums: List[int]) -> int:
        n = len(nums)
        MOD = 10 ** 9 + 7
        sum1 = [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)
        sum2 = [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)
        tp = [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)

        def pushdown(s, t, p):
            m = s + ((t - s) >> 1)
            # 如果当前节点的懒标记非空, 则更新当前节点两个子节点的值和懒标记值
            tp[p*2+1] += tp[p]; add(s, m, p*2+1, tp[p])
            tp[p*2+2] += tp[p]; add(m+1, t, p*2+2, tp[p])
            
            # 清空当前节点的标记
            tp[p] = 0

        def add(s:int, t:int, p:int, k:int):
            sum2[p] += 2 * k * sum1[p] + k * k * (t-s+1) 
            sum1[p] += k * (t-s+1)

        def update(l:int, r:int, s:int, t:int, p:int):
            if l <= s and t <= r:
                add(s, t, p, 1)
                tp[p] += 1
                return
            m = s + ((t - s) >> 1)
            if tp[p] and s != t:
                pushdown(s, t, p)
            if l <= m:
                update(l, r, s, m, p*2+1)
            if r > m:
                update(l, r, m + 1, t, p*2+2)
            
            sum1[p] = (sum1[p*2+1] + sum1[p*2+2]) % MOD
            sum2[p] = (sum2[p*2+1] + sum2[p*2+2]) % MOD

        from collections import defaultdict
        last = defaultdict(lambda: -1)
        ans = 0

        for i in range(n):
            inx = last[nums[i]]
            update(inx+1, i, 0, n-1, 0)
            ans = (ans + sum2[0]) % MOD
            last[nums[i]] = i

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [5,2,4,2,1,3,2,4,3,1]
    print(sol.sumCounts(nums))