# 常用数据结构-前缀异或和-题单
from collections import defaultdict

class Solution:
    def longestAwesome(self, s: str) -> int:
        # 自行解答 
        ans, n = 0, len(s)
        pos = defaultdict(lambda:n)
        
        xors = 0
        for i, ch in enumerate(s):
            d = int(ch)
            xors ^= 1 << d
            if xors.bit_count() <= 1: ans = i+1
            else:
                # ans = max(ans, i-pos[xors]) # it can pass through when comment this line
                for b_p in range(10):
                    if xors >> b_p & 1 and i - pos[xors - (1 << b_p)] > ans:  # 包含则减去
                        ans = i - pos[xors - (1 << b_p)]
                    elif xors >> b_p & 1 == 0 and i - pos[xors + (1 << b_p)] > ans :# 不包含则加上
                        ans = i - pos[xors + (1 << b_p)]
            if pos[xors] > i: pos[xors] = i

        return ans
    
if __name__ == "__main__":
    sol = Solution()
    s = "185801630663498"
    print(sol.longestAwesome(s))