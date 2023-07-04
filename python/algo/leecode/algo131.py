class Solution:
    def partition(self, s: str) :
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            dp[i][i] = True
            if (i>0):
                dp[i][i-1] = True
            for j in range (i+1, n):
                if dp[i+1][j-1] and s[i] == s[j] :
                    dp[i][j] = True
        return self.nextPartition(s, 0, dp)
    
    def nextPartition(self, s:str, begin, dp):
        retValue = []
        if begin == len(s) - 1:
            return [[s[begin:]]]
        for i in range(begin, len(s)):
            if dp[begin][i]:
                if (i == len(s)-1):
                    retValue.append([s[begin:]])
                else: 
                    ret = self.nextPartition(s, i + 1,dp)
                    for part in ret:
                        element = [s[begin:i + 1]] + part
                        retValue.append(element)
        return retValue


if __name__ == "__main__":
    sol = Solution()
    s = "aab"
    print(sol.partition(s))