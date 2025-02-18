# No. 115
class Solution:
    # 题目变更为 LCR 097, equals to No. 115 of main site
    def numDistinct(self, s: str, t: str) -> int:
        '''
        dp[i][j]表示s中前j个字符包含t中前i个字符串出现的次数, 初始化全为0
        1、当s[j] != t[i]时, dp[i][j] = dp[i][j-1]
        即等于s中前j-1个字符包含t中前i个字符串出现的次数, 例如babg包含b的次数
        等于bab包含b的次数

        2、当s[j] == t[i]时, 分三种情况：
        2.1、当j == 0及 i == 0, 即为s及t中第一个字符时, dp[i][j]=1
        2.2 若i == 0, 即遍历s, 包含t中一个字符的次数, 出现一次, 增加1, 
            即dp[i][j] = dp[i][j-1] + 1
        其他情况:
        2.3 当dp[i-1][j-1] = 0, 表明t中i-1个字符在s的j-1无匹配, 
              虽然t[i],s[j]相同, 但整个字符未匹配, 因此dp[i][j] = 0为初始值。
        2.4 当dp[i-1][j-1] > 0的情况下, 表明t中i-1个字符在s的j-1有匹配的情况下
                 dp[i][j] = dp[i-1][j-1] + dp[i][j-1], 
              举例说明, s = "babgbag" t = "bag"
              当i=j=1时, s: ba,  t: ba dp[0][0]=1, 前面字符匹配, 
              dp[1][0] = 0, dp[i][j] = 1 + 0= 1, ba, 匹配ba一次.
              i=1, j=5时, 即babgba包含ba的次数,  dp[1][5] = dp[0][4] + dp[1][4],
              其中dp[1][4], 前babgb包含ba的次数为1, dp[0][4]为3, babgb包含b次数为3,
              s[5]=t[1],即s[5]和前面三个b组合, 匹配t[0]t[1]=ba三次, 因此总次数为4次
        '''
        # n = len(s)
        # m = len(t)
        # if m > n: return 0
        # dp = [[0] * n for _ in range(m)]

        # for i in range(m):
        #     for j in range(i,n):
        #         if s[j] == t[i]:
        #             if i == 0 and j == 0:
        #                 dp[i][j] = 1
        #             elif i == 0:
        #                 dp[i][j] = dp[i][j-1] + 1
        #             elif dp[i-1][j-1] > 0:
        #                 dp[i][j] = dp[i-1][j-1] + dp[i][j-1]
        #             # else 为初始值，忽略
        #         else:
        #             if j > 0: dp[i][j] = dp[i][j-1]
        # return dp[m-1][n-1]

        '''
        2025.2.19 补充
        状态转移方程:
        dp(i,j) = dp(i-1,j) + dp(i-1,j-1)   当 s[i] == s[j]
        dp(i,j) = dp(i-1, j)                当 s[i] != s[j]\
        边界条件:
        dp(i, -1) = 1
        dp(i, j) = 0 i < j
        '''
        
        # 简化边界检查
        n,m  = len(s), len(t)
        if m > n: return 0
        dp = [[0] * (n+1) for _ in range(m+1)]
        for j in range(n):
            dp[0][j] = 1
            
        for i in range(m):
            for j in range(i,n):
                if s[j] == t[i]:
                    dp[i+1][j+1] = dp[i][j] + dp[i+1][j]
                else:
                    dp[i+1][j+1] = dp[i+1][j]
        return dp[m][n]

if __name__ == "__main__":
    sol = Solution()
    # s = "rabbbit"
    # t = "rabbit"
    s = "babgbag"
    t = "bag"
    from datetime import datetime
    begin = datetime.now()
    print(sol.numDistinct(s,t))
    print((datetime.now()- begin).total_seconds())
