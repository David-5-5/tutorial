CAPITALS = "ABCDEFGHIJKLMOPQRSTUVWXYZ"
class Solution:
    def camelMatch(self, queries, pattern: str):
        pat = self.camelLexical(self.addWildcard(pattern))
        result = []
        for query in queries:
            result.append(self.isMatch(self.camelLexical(query), pat))
        return result

    def camelLexical(self, s:str):
        result = []
        begin = 0
        for i in range(1, len(s)):
            if s[i] in CAPITALS:
                result.append(s[begin:i])
                begin = i
        result.append(s[begin:])
        return result
    
                                
    def addWildcard(self, p:str):
        result  = "*"
        for ch in p:
            result = result + ch + "*"
        return result
    
    def isMatch(self, s, p):
        n = len(s)
        m = len(p)
        if n != m:
            return False
        for i in range(n):
            if self.isMatchForEach(s[i], p[i]) == False:
                return False
        return True

    def isMatchForEach(self, s, p) -> bool:
        m, n = len(s), len(p)
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = True
        for i in range(1, n + 1):
            if p[i - 1] == '*':
                dp[0][i] = True
            else:
                break
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if p[j - 1] == '*':
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j]
                elif p[j - 1] == '?' or s[i - 1] == p[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
        return dp[m][n]


if __name__ == "__main__":
    sol = Solution()

    queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"]
    pattern = "FB"
    
    print(sol.camelMatch(queries, pattern))

    queries = ["aksvbjLiknuTzqon","ksvjLimflkpnTzqn","mmkasvjLiknTxzqn","ksvjLiurknTzzqbn","ksvsjLctikgnTzqn","knzsvzjLiknTszqn"]
    pattern = "ksvjLiknTzqn"

    print(sol.camelMatch(queries, pattern))