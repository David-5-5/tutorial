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
            ans = (ans * a * pow(b, -1, MOD)) % MOD

            # 3-th implmenetation, it pass without using pow(b, -1, MOD)
            # for i, c in enumerate(sub, 1):
            #     a = (a*i)
            #     cnt[c] += 1
            #     a //= cnt[c]
            # ans = (ans * a) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.countAnagrams(s = "too hot"))