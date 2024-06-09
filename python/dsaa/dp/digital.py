# 数位 DP 的通用模板
from functools import lru_cache
class DigitalDP:
    
    # refer to leetcode 2376：统计特殊整数
    def countSpecialNumbers(self, n:int):
        s = str(n)

        # i         返回从i开始填数字，
        # mask      i 前面已经选的数字，（可选）遇到不同的题目更改
        # is_limit  前面已经填写的数字是否都是 n 位上的
        # is_num    表示前面是否都是是前导 0 ，如果为 true， 那么当前位从 0 开始，
        #           否则，都是前导 0，从 1 开始或者也跳过
        @lru_cache(maxsize = None)
        def f(i: int, mask: int, is_limit: bool, is_num: bool) -> int:
            if i == len(s):
                return int(is_num)  # is_num 为 True 表示得到了一个合法数字
            res = 0
            if not is_num:  # 可以跳过当前数位, 即取值为 前导零
                res = f(i + 1, mask, False, False)
            
            low = 0 if is_num else 1  # 如果前面没有填数字，必须从 1 开始（因为不能有前导零）
            up = int(s[i]) if is_limit else 9  # 如果前面填的数字都和 n 的一样，那么这一位至多填 s[i]（否则就超过 n 啦）
            for d in range(low, up + 1):  # 枚举要填入的数字 d
                if (mask >> d & 1) == 0:  # d 不在 mask 中
                    res += f(i + 1, mask | (1 << d), is_limit and d == up, True)
            return res
        return f(0, 0, True, False)

    # refer to leetcode 1012
    # sol.numDupDigitsAtMostN(n) + sol.countSpecialNumbers(n) = n
    # It dp could equals to countSpecialNumbers and last return n - f(0, 0, True, False)
    # But I modify the f, add a variable to imply whether or not satify the condition.
    def numDupDigitsAtMostN(self, n:int):
        s = str(n)

        @lru_cache(maxsize = None)
        def f(i: int, mask: int, is_limit: bool, is_num: bool, is_satified:bool) -> int:
            if i == len(s):
                return int(is_num) if is_satified else 0
            
            res = 0
            if not is_num:  # 可以跳过当前数位, 即取值为 前导零
                res = f(i + 1, mask, False, False, False)
            
            low = 0 if is_num else 1  
            up = int(s[i]) if is_limit else 9 
            for d in range(low, up + 1): 
                if (mask >> d & 1) == 1:
                    res += f(i + 1, mask, is_limit and d == up, True, True)
                else:
                    res += f(i + 1, mask | (1 << d), is_limit and d == up, True, is_satified)
            return res
        return f(0, 0, True, False, False)

if __name__ == "__main__":
    sol = DigitalDP()
    print(sol.countSpecialNumbers(1329))
    print(sol.numDupDigitsAtMostN(1329))