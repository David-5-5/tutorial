from functools import cache

# 周赛 356
class Solution:
    def countSteppingNumbers(self, low: str, high: str) -> int:
        # 自行解答，数位DP 包含 low 和 high
        MOD = 10 ** 9 + 7
        
        n = len(high)
        low = low.rjust(n, '0')

        @cache
        def f(i:int, low_limit:bool, up_limit:bool, is_num:bool, prev:int):
            if i == n:
                return 1 if is_num else 0

            lo = int(low[i]) if low_limit else 0
            hi = int(high[i]) if up_limit else 9
            
            ans = 0
            for d in range(lo, hi+1):
                if not is_num or d in  (prev-1,prev+1):
                    ans += f(i+1, low_limit and d==lo, up_limit and d==hi, is_num or d!=0, d)
            return ans % MOD
        
        return f(0, True, True, False, 0)


if __name__ == "__main__":
    sol = Solution()
    low, high = "1", "11"
    low, high = "90", "101"
    print(sol.countSteppingNumbers(low, high))