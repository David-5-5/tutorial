import math
from typing import Counter
from sortedcontainers import SortedDict

# 双周赛 122 自行解答，组合数学
class Solution:
    def countKSubsequencesWithMaxBeauty(self, s: str, k: int) -> int:
        MOD = 10 ** 9 + 7
        h = Counter(s)
        cnt = SortedDict(int)
        for c in h.values(): 
            if c not in cnt: cnt[c] = 1
            else : cnt[c] += 1

        ans = 1
        inx = len(cnt.keys()) # 从最大的key
        while k and inx:
            fc = cnt.keys()[inx-1] # f(c),即 字符 c 在s中出现的次数
            c_ch = cnt[fc]     # 出现次数为 f(c) 的字符数量
            
            if c_ch <= k:
                ans = (ans * pow(fc, c_ch, MOD)) % MOD
                k -= c_ch
            else:
                ans = (ans * math.comb(c_ch, k) * pow(fc, k, MOD)) % MOD
                k = 0
            inx -= 1
        return 0 if k else ans

if __name__ == "__main__":
    sol = Solution()
    s, k = "bcca", 2
    print(sol.countKSubsequencesWithMaxBeauty(s, k))

