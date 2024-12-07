import heapq
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def magicTower(self, nums: List[int]) -> int:
        h, tail = [], []
        cur = 1
        for v in nums:
            while cur + v <= 0: # < 1, 始终为正值，必须>0
                if h and h[0] < v:
                    cur -= h[0]
                    tail.append(heapq.heappop(h))
                else:
                    tail.append(v)
                    v = 0
            cur += v
            if v < 0: heapq.heappush(h, v)
        return len(tail) if sum(tail) + cur >= 0 else -1

if __name__ == "__main__":
    sol = Solution()
    nums = [100,100,100,-250,-60,-140,-50,-50,100,150]
    print(sol.magicTower(nums))