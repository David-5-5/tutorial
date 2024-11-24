import heapq
from typing import List


class Solution:
    def maxRemoval(self, nums: List[int], queries: List[List[int]]) -> int:
        # 参考题解，差分（灵活运用） + 贪心(从左到右遍历，左端点固定，优先选择有端点尽量大的数)
        queries.sort(key=lambda q: q[0]) # 按左端点排序
        n, m,  h = len(nums), len(queries), []
        diff = [0] *  (n+1)
        sum_d = j = 0 # j 是 queries 当前下标
        for i, v in enumerate(nums):
            sum_d += diff[i]
            while j < m and queries[j][0] <= i: # 所有左端点小于等于 i 的入堆
                heapq.heappush(h, -queries[j][1]) # 右端点，大顶堆
                j += 1
            while sum_d < v and h and -h[0] >= i:
                diff[-heapq.heappop(h) + 1] -= 1 # 近需要维护差分数组的右端点
                sum_d += 1 # 差分数组的左+1直接记入 sum_d 中
            if sum_d < v:
                return -1
        return len(h)


if __name__ == "__main__":
    sol = Solution()
    nums, queries = [2,0,2], [[0,2],[0,2],[1,1]]
    print(sol.maxRemoval(nums, queries))