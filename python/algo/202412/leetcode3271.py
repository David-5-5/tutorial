# 双周赛 138
class Solution:
    def stringHash(self, s: str, k: int) -> str:
        # 自行解答
        ans = []
        m = len(s) // k
        for i in range(m):
            ans.append(chr(sum(ord(ch)-ord('a') for ch in s[i*k:(i+1)*k])%26+ord('a')))
        return "".join(ans)