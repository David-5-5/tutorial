class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        # p = self.simple(p)
        m, n = len(s), len(p)
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = True
        for i in range(n//2):
            if p[2 * (i+1) - 1] == "*":
                dp[0][2 * (i+1)] = dp[0][2 * (i+1) - 2]


        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if p[j - 1] == '*':
                    dp[i][j] = (dp[i][j - 1] | dp[i][j-2]) | (dp[i - 1][j] & (p[j-2] == '.' or s[i-1] == p[j-2]))
                elif p[j - 1] == '.' or s[i - 1] == p[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
        return dp[m][n]

    def simple(self, p:str) -> str:
        begin = 0
        part = []
        pos = p.find(".*")
        while pos != -1:
            part.append(p[begin:pos+2])
            begin = pos + 2
            pos = p.find(".*", begin)
        if begin < len(p):
            part.append(p[begin:])

        result = ""
        for i in range(len(part)):
            pat = ""
            if len(part) == i + 1 and part[i].find(".*") == -1:
                return result + part[i];
            pat = part[i]
            while len(pat)>3 and pat[len(pat)-3] == '*':
                pat = pat[0:len(pat)-4] + pat[len(pat)-2:]
            result = result + pat
            
        return result


if __name__ == "__main__":
    sol = Solution()
    
    # s = "baacabacbbcababcbbc"
    # p = "b*a.*b*..a*c*.*"
    # print(sol.isMatch(s, p))
    s = "a"
    p = "c*c*.*"
    print(sol.isMatch(s, p))

    s = "aaabaaaababcbccbaab"
    p = "c*c*.*c*a*..*c*"
    print(sol.isMatch(s, p))

    s = "bbcacbabbcbaaccabc"
    p = "b*a*a*.c*bb*b*.*.*"
    print(sol.simple(p))
    print(sol.isMatch(s, p))