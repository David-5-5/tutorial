from typing import List
from bisect import bisect_left, bisect_right
import math
class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [1] * n
        q = []
        maxN = max(nums)
        for i in range(n):
            if not q:
                q.append((nums[i], dp[i]))
            else:
                right = bisect_left(q, (nums[i],dp[i]))
                left = bisect_left(q, (nums[i]-k,dp[i]))
                for prev in range(left, right):
                    dp[i] = max(dp[i], q[prev][1] + 1)
                
                if right < len(q) and q[right][0] == nums[i]:
                    q[right] = (nums[i], dp[i])
                else:
                    if right < len(q) and dp[i]-nums[i] <= q[right][1]-q[right][0]:
                        continue
                    q.insert(right, (nums[i], dp[i]))

                if right>0 and q[right-1][1]-q[right-1][0]<= q[right][1]-q[right][0]:
                    del q[right-1]

                ql = len(q)
                # If len of the sequent large num is less than inx of q, delete it 
                for i in range(ql-1, right, -1):
                    if q[i][1] <= q[right][1] and q[right][1]+k>=maxN:
                        del q[i]

        return max(dp)

    def lengthOfLIS2(self, nums: List[int], k: int) -> int:
        # 推荐的方案，采用线段树优化DP
        # dp[0..max(nums)-1]为以值1-max(nums)为结尾的最大序列长度, 建立线段树，每个区域为该区域的最大值
        # 具体步骤：
        # 1. 初始化dp[0..max(nums)-1]的线段树的最大值都为0，因为都为零，忽略build步骤
        # 2. 对nums的每个nums[i]元素，执行：
        #   2.1 查询线段树[nums[i]-k, nums[i]-1]区间的最大值，并加1, 并更新线段树dp[nums[i]]的值
        #   2.2 注意边界，当nums[i]=1时，dp[nums] = 1
        n = len(nums)
        maxN = max(nums)
        dp = [0] * (2 ** (math.ceil(math.log(maxN, 2))+1) - 1)
 
        def update(inx:int, val:int, s:int, t:int, p:int):
            # [l, r] 为修改区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if inx == s and inx == t:
                dp[p] = max(val+1, dp[p])
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

        for num in nums:
            r = num - 2
            l = max(0, r - k + 1)
            val = 0 if num == 1 else query(l, r, 0, maxN-1, 0)
            update(num - 1, val, 0, maxN-1, 0)
            
        return max(dp)

if __name__ == "__main__":
    sol = Solution()
    nums, k = [7,4,5,1,8,12,4,7], 5
    nums, k = [1,100,500,100000,100000], 100000
    nums, k = [1, 5], 4
    print(sol.lengthOfLIS(nums, k))
    print(sol.lengthOfLIS2(nums, k))