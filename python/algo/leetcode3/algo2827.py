from functools import lru_cache

# 双周赛 111
# 数位 DP low high
class Solution:
    def numberOfBeautifulIntegers(self, low: int, high: int, k: int) -> int:

        sf = str(high)
        ss = str(low).rjust(len(sf), '0')

        @lru_cache(maxsize=None)
        # 数位 DP 模板 template
        # low_limit 数字的下限
        # upper_limit 数字的下限
        # is_num ： 前导 0
        def f(i:int, low_limit:bool, up_limit:bool, even:int, odd:int, remain:int, is_num:bool):
            if i == len(sf):
                return 1 if even == odd and remain == 0 and is_num else 0

            lo = int(ss[i]) if low_limit else 0
            hi = int(sf[i]) if up_limit else 9
            
            ans = 0
            for d in range(lo, hi+1):
                if not is_num and d == 0:
                    ans += f(i+1, low_limit and d==lo, up_limit and d==hi, even, odd, remain, False)
                else:   
                    ans += f(i+1, low_limit and d==lo, up_limit and d==hi, even + (d%2==0), odd + (d%2==1), (remain*10+d)%k, True)
            return ans
        return f(0, True, True, 0, 0, 0, False)

if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOfBeautifulIntegers(3,31,16))