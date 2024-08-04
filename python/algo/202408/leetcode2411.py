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
                if cnt[e][0] > mn:
                    mn = cnt[e][0]
            if mn == -1: ans.append(1)
            else :ans.append(mn-i+1)

            for e in range(32):
                if v >> e & 1 == 1:
                    cnt[e].pop(0) # 去掉当前元素在 cnt 中相应的指数下标
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [0]
    print(sol.smallestSubarrays(nums))

