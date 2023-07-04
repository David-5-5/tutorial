import random
class Solution:
    def longestDupSubstring(self, s: str) -> str:
        n = len(s)
        maxval, end = 0, -1
        dp = [[None] * n for _ in range(n)]
        for i in range(n-1):
            j = s.find(s[i], i+1)
            while j != -1:
                if i-1 >= 0 and dp[i-1][j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = 1
                if dp[i][j] > maxval:
                    maxval, end = dp[i][j], j
                j = s.find(s[i], j+1)
                
        return s[end-maxval+1:end+1]

    def longestDupSubstring2(self, s: str) -> str:
        def find(m, arr, a1, a2, mod1, mod2):
            n = len(arr)
            h1, h2 = 0, 0
            aL1, aL2 = pow(a1, m, mod1), pow(a2, m, mod2)
            for i in range(m):
                h1 = (h1 * a1 + arr[i]) % mod1
                h2 = (h2 * a2 + arr[i]) % mod2
            
            seen = {(h1, h2)}
            for start in range(1, n-m+1):
                h1 = (h1 * a1 - arr[start-1]*aL1 + arr[start+m-1]) % mod1
                h2 = (h2 * a2 - arr[start-1]*aL2 + arr[start+m-1]) % mod2
                if (h1, h2) in seen:
                    return start
                seen.add((h1,h2))
            return -1
        
        n = len(s)
        l, r = 1, n-1
        m = 0
        codec = [ord(c) - ord('a') for c in s]
        a1, a2 = random.randint(26, 100), random.randint(26, 100)
        mod1, mod2 = 10 ** 9 + 7, 2 ** 31 - 1
        length, start = 0, -1
        while l <= r:
            m = (l + r + 1) // 2
            inx = find(m, codec, a1, a2, mod1, mod2)
            if inx != -1:
                l = m + 1
                length, start = m, inx
            else:
                r = m - 1
        return s[start:start+length] if start != -1 else ""



if __name__ == "__main__":
    sol = Solution()
    #s = "aa"
    s = ""
    for _ in range(3 * (10 ** 4)) : s += 'a'
    print(len(sol.longestDupSubstring2(s)))




