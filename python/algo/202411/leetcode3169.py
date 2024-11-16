from typing import List

# 周赛 400 区间合并 模板
class Solution:
    def countDays(self, days: int, meetings: List[List[int]]) -> int:
        # 类似于 leetcode 56, 排序后 O(N) 的时间复杂度进行区间合并，并计算区间外的天数
        # 不需要 SortDict，这样做比较复杂
        meetings.sort() # meetings.sort(key=lambda p:p[0])
        start, end = 1, 0 # 边界设置，有技巧 end - start + 1 = 0
        for s, e in meetings:
            if s > end:
                days -= end - start + 1
                start = s # 下一个区间
            end = max(end, e) # 存在包含关系
        
        days -= end - start + 1
        return days

    def countDays2(self, days: int, meetings: List[List[int]]) -> int:
        # 另一种边界设置
        meetings.sort() # meetings.sort(key=lambda p:p[0])
        start, end = meetings[0]
        for s, e in meetings[1:]:
            if s > end:
                days -= end - start + 1
                start = s # 下一个区间
            end = max(end, e) # 存在包含关系
        
        days -= end - start + 1
        return days


if __name__ == "__main__":
    sol = Solution()
    days, meetings = 10, [[5,7],[1,3],[9,10]]
    days, meetings = 5, [[2,4],[1,3]]
    print(sol.countDays(days, meetings))