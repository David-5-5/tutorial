from string import ascii_lowercase

# 周赛 305
class Solution:
    def longestIdealString(self, s: str, k: int) -> int:
        cnt = [0] * 26
        for ch in s:
            inx = ascii_lowercase.index(ch)
            cnt[inx] = max(cnt[max(0,inx-k):min(26,inx+k+1)])+1
        
        return max(cnt)

if __name__ == "__main__":
    sol = Solution()
    s, k = "acfgbd", 2
    print(sol.longestIdealString(s, k))