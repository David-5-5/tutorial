from typing import List
import math
class Solution:
    def handleQuery(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        # 结合题意，仅需将nums1建立线段数。 nums2全量更新，不需要建立线段树
        n = len(nums1)

        # segment tree
        # dp is segment tree store sum of district
        # tp is lazy mark for update
        dp = [-1] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)
        tp = [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)

        def build(l:int, r:int, p:int):
            if l == r:
                dp[p] = nums1[l]

            if r > l:
                mid = (l + r) // 2
                build(l, mid, p*2 +1)
                build(mid+1, r, p*2 +2)
                dp[p] = dp[p*2 + 1] + dp[p*2 + 2]

        def pushdown(s, t, p):
            m = s + ((t - s) >> 1)
            # 如果当前节点的懒标记非空, 则更新当前节点两个子节点的值和懒标记值
            dp[p*2+1] = (m - s + 1) - dp[p*2+1]
            dp[p*2+2] = (t - m) - dp[p*2+2]
            # 将标记下传给子节点, 懒惰标记取反. !!!这一点至关重要!!!
            tp[p*2+1], tp[p*2+2] = 1 - tp[p*2+1], 1 - tp[p*2+2]
            # 清空当前节点的标记
            tp[p] = 0           

        def update(l:int, r:int, s:int, t:int, p:int):
            # [l, r] 为修改区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                # 操作1 nums1[i] 取值为[0,1], 执行 nums1[i] ^ 1, 结果反转， 1->0, 0->1
                # 因此区间的和 就是 元素数量 - 当前值， 
                # 例如 如果当前 [l..r] 为 [1 0 1], sum(nums[l..r]) = 2, 执行操作1 
                # 变更为 [0 1 0], sum(nums[l..r]) = 3 - 2 = 1， 因此进行懒惰延迟写时，
                # i) 将区间求和
                dp[p] = (t - s + 1) - dp[p]
                # ii) 懒惰标记取反, 而不是设为 1, !!!这一点至关重要!!!
                # 例如对 [0..n-1]进行两次 [操作1], 相对于回到初始状态，若标记仍在，取消标记即可。
                tp[p] = 1 - tp[p]
                return
            # 当前区间为修改区间的子集时直接修改当前节点的值, 然后打标记, 结束修改
            m = s + ((t - s) >> 1)
            if tp[p] and s != t:
                pushdown(s, t, p)
            if l <= m:
                update(l, r, s, m, p*2+1)
            if r > m:
                update(l, r, m + 1, t, p*2+2)
            
            dp[p] = dp[p*2+1] + dp[p*2+2]

        def getsum(l, r, s, t, p):
            # [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                return dp[p]
            # 当前区间为询问区间的子集时直接返回当前区间的和
            m = s + ((t - s) >> 1)
            if tp[p]:
                pushdown(s, t, p)
            sum = 0
            if l <= m:
                sum = getsum(l, r, s, m, p * 2 + 1)
            if r > m:
                sum = sum + getsum(l, r, m + 1, t, p * 2 + 2)
            return sum

        build(0, n-1, 0)
        ans = []
        # nums2 第一次求和，每个nums2[i] = nums2[i] + nums1[i]*p, 即为
        # 仅需执行一次 sum2 = sum(nums2)
        # 后续每次操作 2， 执行如下即可
        # sum2 += sum(nums1) * p
        sum2 = sum(nums2)

        for q in queries:
            if q[0] == 1:
                update(q[1], q[2], 0, n-1, 0)
            if q[0] == 2:
                sum2 += getsum(0, n-1, 0, n-1, 0) * q[1]
            if q[0] == 3:
                ans.append(sum2)
        return ans
    

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, queries = [1,0,1], [0,0,0], [[1,1,1],[2,1,0],[3,0,0]]
    nums1, nums2, queries = [0,1,0,0,0,0], [14,4,13,13,47,18], [[3,0,0],[1,4,4],[1,1,4],[1,3,4],[3,0,0],[2,5,0],[1,1,3],[2,16,0],[2,10,0],[3,0,0],[3,0,0],[2,6,0]]
    print(sol.handleQuery(nums1, nums2, queries))