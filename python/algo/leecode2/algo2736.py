from collections import defaultdict
from typing import List
from bisect import bisect_left

# 周赛 349
class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        # 方法一 单调栈
        m = len(nums1)
        n = len(queries)
        ans = [-1] * n
        # query 从 x 从高到低 查询
        sortedQueries = [[qi, q[0], q[1]] for qi, q in sorted(enumerate(queries), key=lambda p:p[1], reverse=True)]

        # 按照 x 从高到低排序,
        sortedNums = sorted([[nums1[i], nums2[i]] for i in range(m)], key=lambda p:p[0], reverse=True)
        stack = []
        inx = 0
        # stack 单调栈中元素 (y, x+y), 其中 y 单调递增，x + y 单调递减
        for qi, x, y in sortedQueries:
            while inx < m and sortedNums[inx][0] >= x:
                while stack and stack[-1][1] < sortedNums[inx][0]+sortedNums[inx][1]:
                    stack.pop()
                if not stack or stack[-1][0] < sortedNums[inx][1]:
                    stack.append([sortedNums[inx][1], sortedNums[inx][0]+sortedNums[inx][1]])
                inx += 1
            k = bisect_left(stack, [y,0])
            if k < len(stack):
                ans[qi] = stack[k][1]
        return ans
    
    def maximumSumQueries2(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        m, n = len(nums1), len(queries)
        ans =  [-1] * n

        # 方法二 动态开点线段树
        # query 从 x 从高到低 查询
        sortedQueries = [[qi, q[0], q[1]] for qi, q in sorted(enumerate(queries), key=lambda p:p[1], reverse=True)]
        # 按照 x 从高到低排序,
        sortedNums = sorted([[nums1[i], nums2[i]] for i in range(m)], key=lambda p:p[0], reverse=True)
        j, mx, t = 0, 10 ** 9, SegmentTree()
        for qi, x, y in sortedQueries:
            while j < m and sortedNums[j][0] >= x:
                ax, ay = sortedNums[j]
                t.update(1,1,mx, ay, ax + ay)
                j += 1
            f = t.query(1, 1, mx, y, mx)
            ans[qi] = f
        return ans
            

# 动态开点线段树模板
# 使用 dict
class SegmentTree:
    def __init__(self):
        self.tree = defaultdict()

    # 参数说明
    # o : 当前节点编号，从根节点 1 开始递归
    # l : 开点线段树左区间，从 1 开始递归
    # r : 开点线段树右区间，从 最大值 开始递归
    # i : 当前线段树区间索引  i 在区间 [l, r]
    # val : 当前线段树区间索引的取值 
    def update(self,o: int, l: int, r: int, i: int, val: int) -> None:
        if l == r:
            if o not in self.tree.keys():
                self.tree[o] = val
            else:
                self.tree[o] = max(self.tree[o],val)
            return
        m = (l + r) // 2
        if i <= m: 
            self.update(o * 2, l, m, i, val)
        else:
            self.update(o * 2 + 1, m + 1, r, i, val)
        if o * 2 not in self.tree.keys():
            self.tree[o * 2] = -1
        if o * 2 + 1 not in self.tree.keys():
            self.tree[o * 2 + 1] = -1
        self.tree[o] = max(self.tree[o * 2], self.tree[o * 2 + 1])
    # 参数说明
    # L, R 为查询区间    
    def query(self,o: int, l: int, r: int, L: int, R: int) -> int:  
        if L <= l and r <= R: 
            if o not in self.tree.keys():
                self.tree[o] = -1
            return self.tree[o]
        res = -1
        m = (l + r) // 2
        if L <= m: res = self.query(o * 2, l, m, L, R)
        if R > m: res = max(res, self.query(o * 2 + 1, m + 1, r, L, R))
        return res



if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, queries = [4,3,1,2], [2,4,9,5], [[4,1],[1,3],[2,5]]
    nums1, nums2, queries = [89, 85], [53, 32],[[75,48]]
    print(sol.maximumSumQueries(nums1, nums2, queries))
    print(sol.maximumSumQueries2(nums1, nums2, queries))

