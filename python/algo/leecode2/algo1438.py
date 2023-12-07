from sortedcontainers import SortedDict
from typing import List
class Solution:
    def longestSubarray(self, nums: List[int], limit: int) -> int:
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

if __name__ == "__main__":
    sol = Solution()
    nums, limit = [10,1,2,4,7,2], 5
    print(sol.longestSubarray(nums, limit))
