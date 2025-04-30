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

    def merge2(self, intervals: List[List[int]]) -> List[List[int]]:
        # 差分
        mx = max(p[1] for p in intervals)
        diff = [0] * (2*mx + 2)
        for s, e in intervals:
            diff[s*2] += 1
            diff[e*2+1] -= 1

        a = list(accumulate(diff))
        ans = []
        start = None
        for i, x in enumerate(a):
            if x > 0:
                if start is None:
                    start = i
            else:
                if start is not None:
                    ans.append([start//2, i//2])
                    start = None
        return ans


if __name__ == "__main__":
    sol = Solution()
    intervals = [[1,4],[4,5]]
    print(sol.merge(intervals))