class Solution:
    def ExpandPalindrome(self, s:str, n:int, left:int, right:int) -> int:
        k = 0;
        while left >= 0 and right < n:
            if s[left] == s[right]:
                left -= 1;
                right += 1;
                k += 1;
            else:
                break;
        return k;
    def longestPalindrome(self, s: str) -> str:
        n = len(s);
        if (n <= 0):
            return "";
        result = "";
        # 记录最大回文子串的长度
        # 一旦 s 非空，必然最大回文子串长度至少为 1
        for i in range(n):
            # 考察回文串长度是奇数的情况
            k1 = self.ExpandPalindrome(s, n, i - 1, i + 1);
            # 考察回文串长度是偶数的情况
            k2 = self.ExpandPalindrome(s, n, i, i + 1);
            # 计算两个情况下的长度
            length1 = k1 * 2 + 1;
            length2 = k2 * 2;
            # 更新最大值
            if length1 > len(result):
                result = s[i-k1:i+k1+1];
            if length2 > len(result):
                result = s[i-k2+1:i+k2+1];        
        return result;

if __name__ == "__main__":
    sol = Solution()
    print(sol.longestPalindrome("babad"))