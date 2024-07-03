class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n = len(text1)
        m = len(text2)
        '''
        本题同 剑指 Offer II 095. 最长公共子序列
        自行解答
        动态规划, 状态转移方程dp[i][j]表示text1的前i个字符串和text2的前j个
        字符串的最大公共子序列长度
        1、text1[i] == text2[j]时, 公共子序列长度增1, 状态转移方程为
              dp[i][j] = dp[i-1][j-1] + 1
           其中边界情况下, i == 0 或者 j == 0的情况下, 有序列长度仅为1, 则最长子序列也为1
        2、text1[i] != text2[j]时, 公共子序列长度小于当前字符串的最大值，其状态转移方程为
              dp[i][j] = max(dp[i][j-1], dp[i-1][j])
           其中边界情况下, i == 0 或者 j == 0的情况下, 
              dp[i][j] = dp[i-1][j] 或 
              dp[i][j] = dp[i][j-1]
        '''
        dp = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                if text2[i] == text1[j]:
                    if i == 0 or j == 0:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = dp[i-1][j-1] + 1
                else:
                    if i > 0 and j > 0:
                        dp[i][j] = max(dp[i][j-1], dp[i-1][j])
                    elif i > 0:
                        dp[i][j] = dp[i-1][j]
                    else:
                        dp[i][j] = dp[i][j-1]
        
        return dp[m-1][n-1]

    def longestCommonSubsequence2(self, text1: str, text2: str) -> int:
        n = len(text1)
        m = len(text2)
        '''
        思路同上, 避免i,j小于零的情况, 增加一行，一列
        '''
        dp = [[0] * (n+1) for _ in range(m+1)]

        for i in range(m):
            for j in range(n):
                if text2[i] == text1[j]:
                    dp[i+1][j+1] = dp[i][j] + 1
                else:
                    dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1])
        
        return dp[m][n]

    def longestCommonSubsequence3(self, text1: str, text2: str) -> int:
        n = len(text1)
        m = len(text2)
        '''
        思路同上, 避免i,j小于零的情况, 增加一行，一列
        '''
        dp = [0] * (n+1)
        prev = 0
        # 仅使用一维数组, 提升空间复杂度
        for i in range(m):
            prev = dp[0]
            for j in range(n):
                tmp = dp[j+1]
                if text2[i] == text1[j]:
                    dp[j+1] = prev + 1
                else:
                    dp[j+1] = max(dp[j+1], dp[j])
                prev = tmp
        
        return dp[m]
    
if __name__ == "__main__":
    sol = Solution()
    text1, text2 = "abcde", "ace" 
    text1, text2  = "abc", "ab"
    print(sol.longestCommonSubsequence(text1, text2))
    print(sol.longestCommonSubsequence3(text1, text2))