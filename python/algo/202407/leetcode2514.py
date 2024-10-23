import math
from typing import Counter


class Solution:
    def countAnagrams(self, s: str) -> int:
        MOD = 10 ** 9 + 7
        
        ans = 1
        for sub in s.split():
            a = b = 1
            cnt = Counter()
            # 1-th implmenetation
            a = math.perm(len(sub)) % MOD
            for c in sub:
                cnt[c] += 1
                b = (b*cnt[c]) % MOD
            
            # 2-th implmenetation
            # for i, c in enumerate(sub, 1):
            #     a = (a*i) % MOD
            #     cnt[c] += 1
            #     b = (b*cnt[c]) % MOD
            # 求逆元           
            ans = (ans * a * pow(b, -1, MOD)) % MOD

            # 3-th implmenetation, it pass without using pow(b, -1, MOD)
            # 同位排列组合数相乘 每个单词的同位异构的数量为
            #   n!/k1!k2!..km!
            #   其中 n 为每个单词的长度, k1,.. km 为单词中 m 个字母计数
            # for i, c in enumerate(sub, 1):
            #     a = (a*i)
            #     cnt[c] += 1
            #     a //= cnt[c]
            # ans = (ans * a) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.countAnagrams(s = "too hot"))