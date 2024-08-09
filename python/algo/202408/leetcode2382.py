import heapq
from itertools import accumulate
from math import inf
from typing import List

from sortedcontainers import SortedDict

# 双周赛 85 自行解答 开始未看清题意，使用线段树。由于区间不固定，需要查找区间的最大值
class Solution:
    def maximumSegmentSum(self, nums: List[int], removeQueries: List[int]) -> List[int]:
        # 因此改用 SortedDict 存储区间 key = 区间左端点left value = 区间右端点 right
        # 优先队列排序区间的最大值, 优先队列的元素为(-区间和,left,right )，
        # 同时使用set存放已经被分割的失效区间，配合优先队列使用
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

    def maximumSegmentSum2(self, nums: List[int], removeQueries: List[int]) -> List[int]:
        # 参考题解，使用并查集
        n = len(nums)

        sets = [-inf for _ in range(n)]
        def find(x:int) -> int:
            if sets[x] < 0:
                return x
            else:
                sets[x] = find(sets[x])
                return sets[x]

        def union(u, v):
            rv = find(v)
            if sets[rv] != -inf:
                sets[u] += sets[rv]
                sets[rv] = u
        
        ans = []
        mx = 0
        for i in removeQueries[::-1]:
            ans.append(mx)
            sets[i] = -nums[i]
            if i+1 < n:union(i,i+1)
            if i>0: union(i, i-1)

            if -sets[i] > mx :mx = -sets[i]
        return ans[::-1]

if __name__ == "__main__":
    sol = Solution()
    nums, removeQueries = [1,2,5,6,1], [0,3,2,4,1]
    nums, removeQueries = [500,822,202,707,298,484,311,680,901,319,343,340], [6,4,0,5,2,3,10,8,7,9,1,11]
    print(sol.maximumSegmentSum(nums, removeQueries))
    print(sol.maximumSegmentSum2(nums, removeQueries))