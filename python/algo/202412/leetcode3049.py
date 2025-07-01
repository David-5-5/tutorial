from bisect import bisect_left
from collections import defaultdict, deque
from heapq import heappop, heappush
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def earliestSecondToMarkIndices(self, nums: List[int], changeIndices: List[int]) -> int:
        n, m = len(nums), len(changeIndices)
        total = n + sum(nums)       # 包括 标记 及 dec

        # 快速更新出现的最早下标
        first_t = [-1] * n
        for t in range(m-1, -1, -1):
            first_t[changeIndices[t] - 1] = t   # 直接更新，避免 if 语句

        def check(mx : int) -> bool:
            cnt = 0
            slow = total # 慢速所需天数
            h = []
            for t in range(mx - 1, -1, -1):
                i = changeIndices[t] - 1
                v = nums[i]
                if v <= 1 or t!= first_t[i]:
                    cnt += 1    # 留给左边
                    continue
                if cnt == 0:
                    if not h or v <= h[0]:
                        cnt += 1
                        continue
                    slow += heappop(h) + 1
                    cnt += 2
                slow -= v + 1
                cnt -= 1
                heappush(h, v)
            return cnt >= slow

        # n 为必须的标记时间
        ans = n + bisect_left(range(n, m + 1), True, key=check)
        return -1 if ans > m else ans

if __name__ == "__main__":
    sol = Solution()
    nums, changeIndices = [5,1,3,2,2,5], [3,2,2,3,1,1,3,4,2,3,4,2,5,6,5,3,6,5,3]
    nums, changeIndices = [3,2,3], [1,3,2,2,2,2,3]

    print(sol.earliestSecondToMarkIndices(nums, changeIndices))