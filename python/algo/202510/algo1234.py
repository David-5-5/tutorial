from collections import defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.2 越长越合法/求最短/最小
class Solution:
    def balancedString(self, s: str) -> int:
        # 自行解答
        n, cnt = len(s), defaultdict(int)
        for ch in s :
            cnt[ch] += 1
        
        over, cur = defaultdict(int), defaultdict(int)
        for k, v in cnt.items():
            if v > n // 4:
                over[k] = v - n//4
        
        if len(over) == 0:return 0
        ans, l = n, 0


        for r, ch in enumerate(s):
            if ch in over: cur[ch] += 1
            
            def satis() -> bool :
                for k, v in over.items():
                    if cur[k] < v: return False
                return True
    
            while satis():
                ans = min(ans, r-l+1)
                if s[l] in over: cur[s[l]] -= 1
                l += 1
        return ans
        