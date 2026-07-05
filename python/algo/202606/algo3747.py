class Solution:
    def countDistinct(self, n: int) -> int:
        s = str(n)
        # 9 + 9^2 + ... + 9^(len(s)-1)
        ans = ((9 ** len(s)) - 9) // 8 # 小于 len(s) 位数不包含 0 的数量
        
        for i, ch in enumerate(s):
            d = ord(ch) - ord('0')
            if d == 0: break # 包含 0，后续都不计入
            
            if (i == len(s) - 1): ans += d
            else: ans += (d-1) * (9 ** (len(s)-i-1))
        return ans
