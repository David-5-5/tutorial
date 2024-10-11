from bisect import bisect_left
from collections import deque
from sortedcontainers import SortedDict, SortedList
from typing import List

class Solution:
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        # 2023.12
        begin = 0
        longest = 1
        last = SortedDict()
        for i in range(len(nums)):
            while last and abs(last.peekitem(-1)[0] - nums[i])>limit:
                _, inx = last.popitem(-1)
                begin = max(inx+1, begin)
            while last and abs(last.peekitem(0)[0] - nums[i])>limit:
                _, inx = last.popitem(0)
                begin = max(inx+1, begin)
            # 提升20%的性能
            if begin == i: last.clear()
            last[nums[i]] = i
            longest = max(longest, i-begin+1)
            last.clear()
        return longest


    def longestSubarray2(self, nums: List[int], limit: int) -> int:
        # 用SortedList 更方便
        s = SortedList()
        l = ans = 0
        for r, v in enumerate(nums):
            s.add(v)
            while s and abs(s[-1] - s[0]) > limit:
                s.remove(nums[l])
                l += 1
            ans = max(ans, r - l + 1)
        return ans
        
        # bisect_left有序数组 比 SortedList() 性能差
        # s = []
        # l = ans = 0
        # for r, v in enumerate(nums):
        #     inx = bisect_left(s, v)
        #     s.insert(inx, v)

        #     while s and abs(s[-1] - s[0]) > limit:
        #         inx = bisect_left(s, nums[l])
        #         s.pop(inx)
        #         l += 1
        #     ans = max(ans, r - l + 1)
        # return ans

    def longestSubarray3(self, nums: List[int], limit: int) -> int:
        # 用SortedList 更方便
        # 使用两个单调队列 qmn 存取递增的最小值的索引，qmx 存取 递减的最大值的索引
        # 数组长度即为 在 两个队列头元素的值相差不超过limit的情况下   qmx[0] - qmn[0] + 1
        qmn, qmx = deque(), deque()
        ans = l = 0
        for r, v in enumerate(nums):
            while qmx and nums[qmx[-1]] < v:
                qmx.pop()
            while qmn and nums[qmn[-1]] > v:
                qmn.pop()
            
            qmx.append(r)
            qmn.append(r)

            while qmx and qmn and nums[qmx[0]] - nums[qmn[0]] > limit:
                if qmx[0] == l:
                    qmx.popleft()
                if qmn[0] == l:
                    qmn.popleft()
                l += 1
            ans = max(ans, r-l+1)
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, limit = [10,1,2,4,7,2], 5
    print(sol.longestSubarray3(nums, limit))
