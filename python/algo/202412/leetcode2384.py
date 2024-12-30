
# 贪心专题 - 回文串贪心
from collections import Counter


class Solution:
    def largestPalindromic(self, num: str) -> str:
        cnt = [0] * 10
        ans = ""

        for d in num:
            cnt[int(d)] += 1
        
        for i in range(9,-1,-1):
            val = cnt[i] // 2
            if i or len(ans): 
                ans += str(i) * val
                cnt[i] -= val * 2
        
        mid = ""
        for i in range(9,-1,-1):
            if cnt[i]:
                mid = str(i)
                break
        ans += mid + ans[::-1]

        return ans

    def largestPalindromic2(self, num: str) -> str:
        # 自行解答，用Counter方法
        cnt = Counter(num)
        
        ans = mid = ""
        for i in range(9,-1,-1):
            val = cnt[str(i)] // 2
            if i or len(ans): 
                ans += str(i) * val
                cnt[str(i)] -= val * 2
            
            if len(mid) == 0 and cnt[str(i)]:
                mid = str(i)
        
        ans += mid + ans[::-1]

        return ans