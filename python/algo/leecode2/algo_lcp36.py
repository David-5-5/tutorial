from typing import List
import collections

class Solution:
    # 多维动态规划：
    # dp[i][j] 当前遍历的数为num, i为num+1使用的数量,j表示num+2使用的数量
    # 因此 dp[i][j] 表示当前num与 后续两个数字组成顺子及当前num刻子的数量

    # ############## IMPORTANT ################################
    # 为减少 i, j 的空间, 每个数最多两个和相邻的数组成顺子, 其他都组成刻子

    def maxGroupNumber(self, tiles: List[int]) -> int:
        m = collections.Counter(tiles)
        
        dp = {(0, 0): 0}
        for num in sorted(m):
            ndp=collections.defaultdict(int)
            # x, y, z分别为 num,  num+1  num+2 的数量
            x,y,z=m[num],m[num+1],m[num+2]

            # i, j 表示当前 num, num+1已经使用的数量, 
            # 使用 num, num+1 各自 i, j 数量后, 顺子和刻子的数量: c
            for (i,j),c in dp.items():
                # k in range(3) 表示 num, num+1, num+2 各取出 0 , 1, 2 后组成顺子
                for k in range(3):
                    # 下列的条件含义: 不超过num, num+1, num+3各数的数量
                    if i+k<=x and j+k<=y and k<=z:
                        # c+(x-i-k)//3+k 其中
                        # - c, 上述说明
                        # - (x-i-k)//3 当前 num 减去已使用的 i 及和后续组成顺子 k,  剩下组成刻子的数量
                        # - k, num 与 num+1, num+2 组成顺子的数量
                        ndp[j+k,k]=max(ndp[j+k,k],c+(x-i-k)//3+k)
            dp=ndp
        return max(dp.values())

if __name__ == "__main__":
    sol = Solution()
    tiles = [2,2,2,3,4]
    print(sol.maxGroupNumber(tiles))