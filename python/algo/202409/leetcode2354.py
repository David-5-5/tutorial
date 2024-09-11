from collections import Counter
from itertools import accumulate
from typing import List

# 周赛 303
class Solution:
    def countExcellentPairs(self, nums: List[int], k: int) -> int:
        # 自行解答 
        ns = set(nums)

        cnt = [0] * 30
        res = 0
        for v in ns:
            vc = 0
            for i in range(30):
                if v >> i & 1: vc+=1
            if 2 * vc >= k: res += 1
            for sub in range(max(0, k-vc), 30):
                res += cnt[sub] * 2
            cnt[vc] += 1
        
        return res
   
    def countExcellentPairs2(self, nums: List[int], k: int) -> int:
        if k > 58:return 0
        # 自行解答, 优化 902
        # ns = set(nums)

        # cnt = [0] * 30
        # for v in ns:
        #     vc = 0
        #     for i in range(30):
        #         if v >> i & 1: vc+=1
        #     cnt[vc] += 1

        # 参考题解，调用系统函数
        cnt1 = Counter(x.bit_count() for x in set(nums))
        cnt = [cnt1[i] for i in range(30)]

        pre = list(accumulate(cnt))
        res = 0
        for i in range(1, len(pre)):
            j = max(i, k-i)
            if j >= len(pre): continue
            res += 2 * cnt[i] * (pre[-1] - pre[j-1]) - (cnt[i]*cnt[i] if i==j else 0)

        return res

    def countExcellentPairs2(self, nums: List[int], k: int) -> int:
        # 参考题解，调用系统函数
        cnt = Counter(x.bit_count() for x in set(nums))

        res = 0
        for kx, vx in cnt.items():
            for ky,vy in cnt.items():
                if kx + ky >= k: res += vx * vy
        return res

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,1], 3
    print(sol.countExcellentPairs(nums, k))
    print(sol.countExcellentPairs2(nums, k))