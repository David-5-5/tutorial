import heapq
from itertools import accumulate
from typing import List

from sortedcontainers import SortedDict

# 双周赛 85 自行解答 开始未看清题意，使用线段树。由于区间不固定，需要查找区间的最大值
# 因此改用 SortedDict 存储区间 key = 区间左端点left value = 区间右端点 right
# 优先队列排序区间的最大值, 优先队列的元素为(-区间和,left,right )，
# 同时使用set存放已经被分割的失效区间，配合优先队列使用
class Solution:
    def maximumSegmentSum(self, nums: List[int], removeQueries: List[int]) -> List[int]:
        n = len(nums)
        presum = list(accumulate(nums, initial=0))
        disable = set()
        q = []
        ranges = SortedDict()
        ranges[0] = n-1
        ans = []
        for i in removeQueries:
            inx = ranges.bisect_right(i)
            l, r = ranges.popitem(inx-1)
            disable.add((l, r))

            if l < i:
                ranges[l] = i-1
                heapq.heappush(q, (-presum[i]+presum[l], l, i-1))

            if r > i:
                ranges[i+1] = r
                heapq.heappush(q, (-presum[r+1]+presum[i+1], i+1, r))
            
            while q and (q[0][1], q[0][2]) in disable:
                disable.remove((q[0][1], q[0][2]))
                heapq.heappop(q)
            
            ans.append(-q[0][0]) if q else ans.append(0)
        return ans



if __name__ == "__main__":
    sol = Solution()
    nums, removeQueries = [1,2,5,6,1], [0,3,2,4,1]
    nums, removeQueries = [500,822,202,707,298,484,311,680,901,319,343,340], [6,4,0,5,2,3,10,8,7,9,1,11]
    print(sol.maximumSegmentSum(nums, removeQueries))