from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        ans = 0
        courses.sort(key=lambda p:(p[1],p[0], p[0]))

        cur = 0
        for d, last in courses:
            if cur + d > last:continue
            cur += d
            ans += 1
        return ans
