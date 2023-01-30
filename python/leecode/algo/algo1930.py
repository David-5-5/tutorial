class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        n = len(s)
        result = 0
        for i in range(26):
            l, r = 0, n-1
            while l < n and ord(s[l]) - ord('a') != i:
                l += 1
            while r >=0 and ord(s[r]) - ord('a') != i:
                r -= 1
            if r - l < 2:
                continue
            charset = set()
            for k in range(l+1, r):
                charset.add(s[k])
            result += len(charset)

        return result

    def countPalindromicSubsequence2(self, s: str) -> int:
        n = len(s)
        result = 0
        pre = [0] * n
        suf = [0] * n

        for i in range(n):
            pre[i] = (pre[i-1] if i else 0) | 1 << ord(s[i]) - ord('a')
        for i in range(n-1, -1 , -1):
            suf[i] = (suf[i+1] if i == n-1 else 0) | 1 << ord(s[i]) - ord('a')
        
        ans = [0] * 26
        for i in range(1, n-1):
            ans[ord(s[i]) - ord('a')] |= pre[i-1] & suf[i+1]

        for i in range(26):
            result += bin(ans[i]).count("1")
        return result

if __name__ == "__main__":
    sol = Solution()
    s= "aabca"
    print(sol.countPalindromicSubsequence(s))        