# 双周赛 92
class Solution:
    def countPalindromes(self, s: str) -> int:
        # 参考题解，前后缀分解
        suf = [0]  * 10
        suf2 = [0] * 100
        for d in reversed(s):
            for d2 in range(10):
                suf2[d2*10 + int(d)] += suf[d2]
            suf[int(d)] += 1

        pre = [0]  * 10
        pre2 = [0] * 100
        ans = 0
        for d in s:
            suf[int(d)] -= 1
            for d2 in range(10):
                suf2[d2*10+int(d)] -= suf[d2]

            for i in range(100):
                #前后缀的 i 值是相同的，后缀倒序生成，正好形成回文
                ans += pre2[i] * suf2[i]

            for d2 in range(10):
                pre2[d2*10 + int(d)] += pre[d2]
            pre[int(d)] += 1
        
        return ans % (10**9 + 7)


    # dynamic programing, but the Time Complexity is not satisfied
    def countPalindromes2(self, s: str) -> int:

        n = len(s)
        dp1 = [[i-j+1 if (i>=j) else 0 for i in range(n)] for j in range(n)]
        dp3 = [[0] * n for _ in range(n)]
        dp5 = [[0] * n for _ in range(n)]

        for i in range(n-3, -1, -1):
            for j in range(i+2, n):
                dp3[i][j] = dp3[i+1][j] + dp3[i][j-1] - dp3[i+1][j-1]
                if s[i] == s[j]:
                    dp3[i][j] += dp1[i+1][j-1]

        for i in range(n-5, -1, -1):
            for j in range(i+4, n):
                dp5[i][j] = dp5[i+1][j] + dp5[i][j-1] - dp5[i+1][j-1]
                if s[i] == s[j]:
                    dp5[i][j] += dp3[i+1][j-1]

        return dp5[0][n-1] % (10 ** 9 + 7)



if __name__ == "__main__":
    sol = Solution()
    s = "000000" 
    print(sol.countPalindromes(s))
    print(sol.countPalindromes2(s))