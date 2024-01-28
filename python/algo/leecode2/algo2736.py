from typing import List
from bisect import bisect_left
class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        m = len(nums1)
        n = len(queries)
        ans = [-1] * n
        sortedQueries = [[qi, q[0], q[1]] for qi, q in sorted(enumerate(queries), key=lambda p:p[1], reverse=True)]
        sortedNums = sorted([[nums1[i], nums2[i]] for i in range(m)], key=lambda p:p[0], reverse=True)
        stack = []
        inx = 0
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

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, queries = [4,3,1,2], [2,4,9,5], [[4,1],[1,3],[2,5]]
    nums1, nums2, queries = [89, 85], [53, 32],[[75,48]]
    print(sol.maximumSumQueries(nums1, nums2, queries))

