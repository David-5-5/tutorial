import heapq
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        # 贪心，怎么贪？怎么用好给的信息和变量？
        # 按照 lastday 从小到大排序
        ans = 0
        courses.sort(key=lambda p:p[1])

        h = []
        cur = 0
        for d, last in courses:
            if d > last:continue
            
            # 如果课程无法完成且堆顶的元素课程时间大于当前课程
            # 堆顶元素出堆，完成课程少的课程，为后续的课程节约时间
            if d + cur > last and h and -h[0] > d:
                mx_d = heapq.heappop(h)
                cur += mx_d
            
            # 能够在lastday时间内完成课程，入堆
            if d + cur <= last:
                heapq.heappush(h, -d)
                cur += d
                # 堆的最大长度即为最大课程数
                if len(h) > ans: ans = len(h) 

        return ans
