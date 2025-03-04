from typing import List

# 区间合并 模板
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        # 类似于 3169 排序后合并区间，瓶颈在排序
        intervals.sort(key= lambda p:p[0])

        ans = []
        left, right = intervals[0]
        for l, r in intervals[1:]:
            if l > right:
                ans.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        ans.append([left, right])

        return ans


if __name__ == "__main__":
    sol = Solution()
    intervals = [[1,4],[4,5]]
    print(sol.merge(intervals))