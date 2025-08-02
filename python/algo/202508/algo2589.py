from typing import List
from bisect import bisect_left

# 同 lcp32 
# 常用数据结构 - 8.4 Lazy 线段树（有区间更新）
class Solution:
    def findMinimumTime(self, tasks: List[List[int]]) -> int:
        # The elment is tuple with (l,r,d), where d is prefix sum of duration
        # The first piont, similiar to the first element of prefix sum
        # The defualt l, r set to -2, because the left begin at 0,
        # When conjunction the segments, the -1, 0  is adjacent, it will 
        # result in the fisrt element be poped and the bisect_left(st, (start,)) - 1 < 0
        st = [(-2, -2, 0)]
        tasks.sort(key=lambda k:k[1])

        for start, end, d in tasks:
            _, r, du = st[bisect_left(st, (start,)) - 1]
            # subtract the duration of segments which the [start, end] contains
            d -= st[-1][2] - du
            if start <= r:
                d -= r - start + 1
            if d <=0:continue

            # [5,6] and [7,9] is adjacent
            while end - d  + 1 <= st[-1][1] + 1:
                l, r, _ = st.pop(-1)
                d += r - l + 1
            st.append((end - d + 1,end, d + st[-1][2]))
        
        return st[-1][2]

if __name__ == "__main__":
    sol = Solution()
    tasks = [[2,3,1],[5,5,1],[5,6,2]]
    tasks = [[0,0,1],[1,1,1],[2,2,1]]
    print(sol.processTasks(tasks))