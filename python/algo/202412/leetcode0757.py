from typing import List

# 贪心专题 区间选点
class Solution:
    def intersectionSizeTwo(self, intervals: List[List[int]]) -> int:
        # 方法类似于 leetcode 452
        intervals.sort(key=lambda p:p[1]) 

        ans = 2
        last = [intervals[0][1]-1, intervals[0][1]]
        for l, r in intervals[1:]:
            if l<=last[0]:continue
            if l<=last[1]:
                if r==last[1]:last.insert(1,r-1) # 需要考虑这种情况，插入r-1
                else: last.append(r)
            else:
                last.extend([r-1, r])
            
            ans += len(last) - 2
            last = last[-2:]
        return ans        