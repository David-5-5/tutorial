from functools import lru_cache
class Solution:
    
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:

        sf = str(finish)
        ss = str(start).rjust(len(sf), '0')
        diff = len(sf) - len(s)

        @lru_cache(maxsize=None)
        def f(i:int, low_limit:bool, up_limit:bool):
            if i == len(sf):
                return 1

            lo = int(ss[i]) if low_limit else 0
            hi = int(sf[i]) if up_limit else 9

            ans = 0
            if i < diff:
                for d in range(lo, min(hi+1,limit+1)):
                    ans += f(i+1, low_limit and d==lo, up_limit and d==hi)
            else:
                x = int(s[i-diff])
                if lo <= x <= min(hi,limit):
                    ans += f(i+1, low_limit and x==lo, up_limit and x==hi)
            return ans
        return f(0, True, True)
    

if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOfPowerfulInt(1, 6000, 4, "124"))