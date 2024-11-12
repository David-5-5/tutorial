from functools import cache


class Solution:
    def kInversePairs(self, n: int, k: int) -> int:
        '''
        动态规划
        dp[i][j]  0<=i<n, 0<=j<=k
        表示i之前, j个逆序列的数量状态转移方程如下, 
        dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-i-1] ; where j-i-1 >=0
        举例说明 n = 10 k = 10
        dp[5][9], 其中
        i = 5, 表示数字6, 可以提供0~5个逆序, 
            如果6在最前面, 6大于其他5个数字, 提供5个逆序; 
            如果6在第二位, 6大于后面4个数字, 提供4个逆序; 以此类推
            如果在最后, 提供0个逆序
        因此dp[5][9] = dp[4][9] + dp[4][8] + dp[4][7] + dp[4][6] + dp[4][5] + dp[4][4]
        dp[4][9]表示前5个数字提供9个逆序, 6在最后, 提供0个逆序
        dp[4][7]表示前5个数字提供7个逆序, 6在倒数第二, 提供2个逆序, 以此类推

        计算技巧说明:
        dp[i][j]计算过程中, j从0开始, 因此循环计算的过程如下:
        dp[5][0] = dp[4][0] (j-1 ~ j-i-1)小于零忽略
        dp[5][1] = dp[4][1] + dp[4][0]
        ...
        dp[5][7] = dp[4][7] + dp[4][6] + dp[4][5] + dp[4][4] + dp[4][3] + dp[4][2]
        dp[5][8] = dp[4][8] + dp[4][7] + dp[4][6] + dp[4][5] + dp[4][4] + dp[4][3]
        计算dp[5][9], 上式 - dp[4][3] + dp[4][9]
        '''
        dp = [[0]* (k+1) for _ in range(n)]
        dp[0][0] = 1

        for i in range(1, n):
            cum = 0
            for j in range(k+1):
                cum += dp[i-1][j]
                if j-i>0 : cum -= dp[i-1][j-i-1] # 计算技巧
                dp[i][j] = cum % (10 ** 9 + 7)

        return dp[n-1][k]


    def kInversePairs2(self, n: int, k: int) -> int:
        # 参考 3193 题解
        # 最好理解的方式递归
        # 状态转移方程 dp(i, j) += dp(i-1, j-k)
        # 其中  1: dp(i, j) 表示前 i 个数字包含 j 个逆序对的数量
        #       2: i 从 i - 1转移过来，增加了 k 个逆序对
        # 但是时间复杂度 O(n^2k)
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0:
                if j == 0: return 1
                else: return 0
            if j < 0: return 0 # 剪枝
            return sum(dfs(i-1,j-t) for t in range(min(i,j)+1)) % (10 ** 9 + 7)
        
        return dfs(n-1, k)

    def kInversePairs3(self, n: int, k: int) -> int:
        # 从 kInversePairs2，递归修改为递推再进行优化
        # 即是 kInversePairs 方法

if __name__ == "__main__":
    sol = Solution()
    print(sol.kInversePairs(300,400))
    print(sol.kInversePairs2(300,400))