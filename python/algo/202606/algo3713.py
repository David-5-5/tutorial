class Solution:
    def longestBalanced(self, s: str) -> int:
        # 暴力
        ans, n = 0, len(s)
        for i in range(n):
            cnt = [0] * 26
            if n - i < ans: break
            for j in range(i, n):
                cnt[ord(s[j])-ord('a')] += 1
                mx = max(cnt)
                if all(x == mx or x == 0 for x in cnt) and j-i+1>ans:
                    ans = j - i + 1
        
        return ans
