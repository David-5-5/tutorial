from bisect import bisect_left
from collections import defaultdict
from itertools import pairwise
from typing import List


class BIT:
    # 数组从零开始
    def __init__ (self, n:int) -> None:
        self.nums = [0] * n

    # 固定 +1
    def add(self, i:int):
        while i < len(self.nums):
            self.nums[i] += 1
            i += i & -i

    def query(self, i:int) ->int:
        res = 0
        while i > 0:
            res += self.nums[i]
            i -= i & -i # i &= i - 1
        return res


class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        x_h, y_h = defaultdict(list), defaultdict(list)
        
        for x, y in zip(xCoord, yCoord):
            x_h[x].append(y)
            y_h[y].append(x)
        
        # for k in x_h.keys(): x_h[k].sort()
        # for k in y_h.keys(): y_h[k].sort()

        # 预处理每个点的正下方的点
        below = {}
        for x, ys in x_h.items():
            ys.sort()
            for y1, y2 in pairwise(ys):
                below[(x, y2)] = y1
        
        left = {}
        for y, xs in y_h.items():
            xs.sort()
            for x1, x2 in pairwise(xs):
                left[(x2, y)] = x1
        
        # 离散化用
        x_sorted = sorted(x_h)
        y_sorted = sorted(y_h)

        print(x_sorted)
        # 离线查询，
        
        # 收集询问，即合法的矩形区域中点的个数
        queries = []
        # 枚举(x2, y2) 为矩形的右上角
        for x2, list_y in x_h.items():
            for y1, y2 in pairwise(list_y): # 上述代码预处理已排序
                x1 = left.get((x2, y2), None)
                if x1 is not None and left.get((x2, y1))== x1 and below.get((x1,y2),None) == y1:
                    queries.append((bisect_left(x_sorted, x1),
                            bisect_left(x_sorted, x2),
                            bisect_left(y_sorted, y1),
                            bisect_left(y_sorted, y2),
                            (y2-y1)*(x2-x1)))

        # 离线询问
        grouped_queries = [[] for _ in range(len(x_sorted))]
        for i, (x1, x2, y1, y2, _) in enumerate(queries):
            if x1 > 0:
                grouped_queries[x1-1].append((i,-1, y1, y2))
            grouped_queries[x2].append((i, 1, y1, y2))
        
        # 回答询问
        res = [0] * len(queries)
        tree = BIT(len(y_sorted)+1)

        for x, qs in zip(x_sorted, grouped_queries):
            # 把横坐标为 x 的所有点都加到 tree 中
            for y in x_h[x]:
                tree.add(bisect_left(y_sorted, y) + 1) # 离散化
            for qid, sign, y1, y2 in qs:
                res[qid] += sign * (tree.query(y2+1)-tree.query(y1))
        
        ans = -1
        for cnt, q in zip(res, queries):
            if cnt == 4:
                ans = max(ans, q[4])
        return ans

if __name__ == "__main__":
    sol = Solution()
    