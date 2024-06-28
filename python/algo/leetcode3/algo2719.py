from functools import lru_cache


class Solution:
    def count(self, num1: str, num2: str, min_sum: int, max_sum: int) -> int:

        ss = str(num1).rjust(len(num2), '0')

        @lru_cache(maxsize=None)
        def f(i:int, ds:int, low_limit:bool, up_limit:bool):
            if i == len(num2):
                return 1 if min_sum <= ds <= max_sum else 0

            lo = int(ss[i]) if low_limit else 0
            hi = int(num2[i]) if up_limit else 9
            
            ans = 0
            for d in range(lo, hi+1):
                ans += f(i+1, ds+d, low_limit and d==lo, up_limit and d==hi)
            return ans % (10 ** 9 + 7)
        return f(0, 0, True, True)

if __name__ == "__main__":
    sol = Solution()
    print(sol.count("4179205230", "7748704426", 8, 46))