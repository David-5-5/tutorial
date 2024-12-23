from collections import Counter
from itertools import accumulate
from math import inf
from typing import List

# 双周赛 135
class Solution:
    def minChanges(self, nums: List[int], k: int) -> int:
        # 参考题解
        # p, q = nums[i], nums[n-i-1], 令 p < q
        # 存在如下几种情况
        # 1, q - p = X 无需修改
        # 2, q - p > X 修改一个数即可
        # 3, q - p < X, 且 max(q, k-p) >= X 那么修改一个数即可
        # 4, q - p < X, 且 max(q, k-p) < X, 那么修改两个数即可
        # 枚举 X 的 值 0, 1, 2, ... k
        # X = 0 修改次数 = n//2 - cnt[0]， 其中 cnt[0] 表示p-q = 0 的数量
        # X = 1 修改次数 = n//2 - cnt[1] + cnt2[0], 其中 cnt2[0] 表示max(q,k-p) < 1的数量
        # X = 2 修改次数 = n//2 - cnt[2] + cnt2[0] + cnt2[1], 表示max(q,k-p) < 2
        #  ..........                       ..........
        # X = i 修改次数 = n//2 - cnt[2] + cnt2[0] + cnt2[1] + ... + cnt2[i-1], 表示max(q,k-p) < i
        #     前缀和 presum[i] = cnt2[0] + cnt2[1] + ... + cnt2[i-1]
        # X = i 修改次数 = n//2 - cnt[2] + presum[i], 其中 presum[i] 为 cnt2 的前缀和

        n = len(nums)
        cnt = Counter([abs(nums[i]-nums[n-i-1]) for i in range(n//2)])
        mx = [0] * (k+1)
        for i in range(n//2):
            p, q = nums[i],nums[n-1-i]
            if p > q:
                p, q = q, p
            mx[max(q, k-p)] += 1
        
        sum2 = 0
        ans = inf
        for x in range(k+1):
            ans = min(ans, n // 2 - cnt[x] + sum2)
            sum2 += mx[x]
        return ans

    def minChanges2(self, nums: List[int], k: int) -> int:
        n = len(nums)
        diff = [0] * (k+2)
        for i in range(n//2):
            p, q = nums[i],nums[n-1-i]
            if p > q:
                p, q = q, p
            x = q - p
            mx = max(q, k-p)
            # [0,x-1]   : +1
            diff[0] += 1
            diff[x] -= 1 # x == 0 时抵消了
            # [x+1, mx] : +1
            diff[x+1] += 1
            # diff[mx+1] -= 1

            # [mx+1, k] : +2
            diff[mx+1] += 1 # 抵消上一条
        return min(accumulate(diff))

if __name__ == "__main__":
    sol = Solution()
    nums, k = [0,1,2,3,3,6,5,4], 6
    print(sol.minChanges(nums, k))
    print(sol.minChanges2(nums, k))
