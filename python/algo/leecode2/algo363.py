from typing import List
from bisect import bisect_right
class Solution:
    def maxSumSubmatrix(self, matrix: List[List[int]], k: int) -> int:
        # 求二维数组/矩阵前缀和
        rows = len(matrix)
        cols = len(matrix[0])
        # 矩阵按列求一维数组的前缀和, 便于将二维数组转换为一维数组
        sum_by_col = [[0] * cols for _ in range(rows)]

        for i in range(rows):
            for j in range(cols):
                sum_by_col[i][j] = (sum_by_col[i-1][j] if i >0 else 0) + matrix[i][j]

        ans = -float("inf")
        
        for r1 in range(rows):
            for r2 in range(r1, rows):
                prefix = []
                pres = 0
                for col in range(cols):
                    # 将R1到R2行按列合并为一行, 并计算一维数组的前缀和
                    # 从第一个元素开始, 计算前缀和, 并将前缀和与k进行比较
                    # 1.等于k,直接返回k
                    # 2.presum - k, 二分查找前序的前缀和是否存在等于presum - k,
                    #   2.1若存在表明当前列c2减去前序的c1列前缀和等于k, 
                    #   2.2不存在等于presum - k,则找出大于presum - k的最小值,即为不超过k的最大值
                    # 3.将当前presum加入排序的列表中
                    # 4.遍历后续元素
                    pres += sum_by_col[r2][col] - \
                            (sum_by_col[r1-1][col] if r1>0 else 0)
                    if pres == k:
                        return k
                    if pres < k:
                        ans = max(ans, pres)
                    inx = bisect_right(prefix, pres-k)
                    if prefix and inx > 0 and prefix[inx-1] == pres-k:
                        return k
                    elif prefix and inx < len(prefix):
                        ans = max(ans, pres - prefix[inx])
                    # Add current prefix
                    inx = bisect_right(prefix, pres)
                    prefix.insert(inx, pres)

        return ans


if __name__ == "__main__":
    sol = Solution()
    matrix, k = [[2,2,-1]], 0
    matrix, k = [[5,-4,-3,4],[-3,-4,4,5],[5,1,5,-4]], 10
    print(sol.maxSumSubmatrix(matrix, k))