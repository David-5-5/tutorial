from functools import lru_cache
class Solution:
    # 数位 DP
    # refer to python/dsaa/dp/digital.py
    def numberOf2sInRange(self, n: int) -> int:
        s = str(n)

        # 模板中的 is_num 多余，前导 0 不计入 count
        @lru_cache(maxsize = None)
        def f(i: int, is_limit: bool, count:int) -> int:
            if i == len(s):
                return count
            
            res = 0
            up = int(s[i]) if is_limit else 9  
            for d in range(up + 1):
                if d == 2:
                    res += f(i + 1, is_limit and d == up, count+1)
                else:
                    res += f(i + 1, is_limit and d == up, count)
            return res
        return f(0, True, 0)

    # refer to algo 233 (数字 1 出现的次数), 使用数学枚举的方法
    # 计算数字 2 出现的次数 
    def numberOf2sInRange2(self, n: int) -> int:
        strn = str(n)

        lenn = len(strn)

        def toint(begin: int, end:int):
            if begin >= end:
                return 0
            else:
                return int(strn[begin:end])
        cnt = 0
        for i in range(lenn):
            prec = toint(0,i) + 1
            subc = toint(i+1, lenn) + 1
            cnt += (prec - 1) * (10 ** (lenn-i-1))
            if int(strn[i]) == 2:
                cnt += subc
            elif int(strn[i]) > 2:
                cnt += (10 ** (lenn-i-1))
        return cnt

if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOf2sInRange(21115))
    print(sol.numberOf2sInRange2(21115))  