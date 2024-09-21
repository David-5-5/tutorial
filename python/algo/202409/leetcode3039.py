# 双周赛 124
class Solution:
    def lastNonEmptyString(self, s: str) -> str:
        lett = [[-1,0] for _ in range(26)]
        mx = 0
        for i, ch in enumerate(s):
            lett[ord(ch)-ord('a')][0] = i
            lett[ord(ch)-ord('a')][1] += 1
            if lett[ord(ch)-ord('a')][1] > mx:
                mx = lett[ord(ch)-ord('a')][1]
        
        ans = ""
        for i, (_, cnt) in sorted(enumerate(lett), key=lambda p:p[1]):
            if mx == cnt:
                ans += chr(ord('a')+i)
        return ans

if __name__ == "__main__":
    sol = Solution()
    s = "aabcbbca"
    print(sol.lastNonEmptyString(s))