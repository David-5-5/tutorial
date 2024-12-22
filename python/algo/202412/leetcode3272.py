from collections import Counter, defaultdict
from math import factorial, perm


class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        # 枚举半回文，检查全回文是否整除 k
        # 检查字母异位词分组是否存在
        lower = 10 ** ((n-1)//2) # 半回文，对于奇数包括中间数字
        ans, vis = 0, set()

        for i in range(lower, lower * 10):
            val = str(i)
            val += val[::-1][n%2:] # 组成完整数字，对于奇数，少取一位
            if int(val) % k: continue

            cnt = Counter(val)
        
            key = "".join(sorted(val))
            if key in vis: continue

            vis.add(key)
            comb = (n - cnt['0']) * perm(n-1)
            for v in cnt.values():
                comb //= perm(v)
            ans += comb

        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.countGoodIntegers(3, 5)) 