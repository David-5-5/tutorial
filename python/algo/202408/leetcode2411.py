from collections import defaultdict
from math import inf
from typing import List

# 双周赛 87
class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        # 自行解答，性能较差 O(96 * N)
        cnt = defaultdict(list)
        
        # lowbit
        for i, v in enumerate(nums):
            for e in range(32):
                if v >> e & 1 == 1:
                    cnt[e].append(i)
        for e in range(32):
            cnt[e].append(-1)
        
        ans = []
        for i, v in enumerate(nums):
            mn = -1
            for e in range(32):
                if v >> e & 1 == 1:
                    if i > mn: mn = i
                    cnt[e].pop(0)
                elif cnt[e][0] > mn:
                    mn = cnt[e][0]
            if mn == -1: ans.append(1)
            else :ans.append(mn-i+1)

        return ans     

    def smallestSubarrays2(self, nums: List[int]) -> List[int]:
        # 自行解答，倒序一次遍历，这次好多了，不过应该还有优化空间
        bitlen = max(nums).bit_length() + 1 # 时间是固定 32 位的一半
        cnt = [-1] * bitlen
        n = len(nums)
        # lowbit
        ans = [1] * n
        for i in range(n-1,-1,-1):
            v = nums[i]
            mn = -1
            for e in range(bitlen):
                if v >> e & 1 == 1:
                    cnt[e] = i
                    if i > mn: mn = i
                elif cnt[e] > mn:
                    mn = cnt[e]
            if mn != -1:  ans[i] = mn-i+1

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,0,2,1,3]
    print(sol.smallestSubarrays(nums))
    print(sol.smallestSubarrays2(nums))

