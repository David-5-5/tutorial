from typing import List
class Solution:
    def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:
        # 求二维数组/矩阵前缀和
        rows = len(matrix)
        cols = len(matrix[0])
        # 矩阵按列求一维数组的前缀和, 便于将二维数组转换为一维数组
        sum_by_col = [[0] * cols for _ in range(rows)]

        for i in range(rows):
            for j in range(cols):
                sum_by_col[i][j] = (sum_by_col[i-1][j] if i >0 else 0) + matrix[i][j]

        res = 0
        # 求二维数组/矩阵任意子矩阵的和等于target
        # 每个前缀的值, 创建哈希统计出现的次数. presum[cur] - target, 找出其余数的次数.
        # 即presum[cur] - presum[i] == target, 即需要presum[i] == presum[cur] - target
        # 按要去,不需要具体的位置, 因此从哈希表中查找presum[cur] - target的出现的次数即可
        # 当presum[cur] == target时, 次数也需要加 1
        for r1 in range(rows):
            for r2 in range(r1, rows):
                # key is prefix sum, the value is times
                dict_pres = {}
                pres = 0
                for col in range(cols):
                    # 将R1到R2行按列合并为一行, 并计算一维数组的前缀和
                    pres += sum_by_col[r2][col] - \
                            (sum_by_col[r1-1][col] if r1>0 else 0)
                    if pres == target:
                        res += 1
                    if pres-target in dict_pres.keys():
                        res += dict_pres[pres-target]
                    if pres in dict_pres.keys():
                        dict_pres[pres] += 1
                    else:
                        dict_pres[pres] = 1

        return res

if __name__ == "__main__":
    sol = Solution()
    matrix = [[1,-1],[-1,1]]
    print(sol.numSubmatrixSumTarget(matrix, 0))