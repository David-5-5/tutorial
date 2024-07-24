from typing import List

# 双周赛 93
# 采用贪心，思维能力。也可以二分查找
class Solution:
    def maxJump(self, stones: List[int]) -> int:
        n = len(stones)
        return max([stones[i] - (stones[i-2] if i > 1 else stones[i-1]) for i in range(1, n)])

        
