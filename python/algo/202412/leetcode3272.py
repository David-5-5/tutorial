from collections import Counter, defaultdict
from math import factorial, perm


class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        # 枚举半回文，检查全回文是否整除 k
        # 检查字母异位词分组是否存在

        if n == 1:
            return sum(1 if v % k == 0 else 0 for v in range(1, 10))

        lower = 10 ** (n//2 - 1)
        upper = 10 ** (n // 2)
        mid = n % 2
        
        ans = 0
        if mid:
            for m in range(0, 10):
                h = set()
                for i in range(lower, upper):
                    pre = str(i)
                    
                    cnt = defaultdict(int)
                    cnt[m] += 1
                    for digit in pre:
                        cnt[int(digit)] += 2
                
                    key = "".join(sorted(pre))
                    if key in h: continue
                    
                    val = i * 10 ** (n-(n//2)) + m * 10  ** (n//2) + int(pre[::-1])
                    if val % k == 0:
                        h.add(key)
                        comb = (n - cnt[0])*perm(n-1)
                        for v in cnt.values():
                            comb //= perm(v)
                        ans += comb
        else:
            h = set()
            for i in range(lower, upper):
                pre = str(i)
                
                cnt = defaultdict(int)
                for digit in pre:
                    cnt[int(digit)] += 2
            
                key = "".join(sorted(pre))
                if key in h: continue
                
                val = i * 10 ** (n-(n//2)) + int(pre[::-1])
                if val % k == 0:
                    h.add(key)
                    comb = (n - cnt[0])*perm(n-1)
                    for v in cnt.values():
                        comb //= perm(v)
                    ans += comb
        return ans




if __name__ == "__main__":
    sol = Solution()
    print(sol.countGoodIntegers(4, 5))
    print(sol.countGoodIntegers2(4, 5))    