from functools import lru_cache
from typing import List
class Solution:
    # 数位 DP
    # refer to python/dsaa/dp/digital.py
    def atMostNGivenDigitSet(self, digits: List[str], n: int) -> int:
        s = str(n)

        @lru_cache(maxsize = None)
        def f(i: int, is_limit: bool, is_num: bool) -> int:
            if i == len(s):
                return int(is_num)
            res = 0
            if not is_num:
                res = f(i + 1, False, False)
            
            up = int(s[i]) if is_limit else 9
            for d in digits:
                if is_limit and d > s[i]: continue
                res += f(i + 1, is_limit and int(d) == up, True)
            return res
        return f(0, True, False)

if __name__ == "__main__":
    sol = Solution()
    digits, n = ["1","3","5","7"], 100
    print(sol.atMostNGivenDigitSet(digits, n))