from functools import cache


depth = [0] * 51
for i in range(2, 51):
    depth[i] = depth[i.bit_count()] + 1

class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        # 自行解答
        if k == 0: return 1  # 边界情况 WA 两次
        sf = bin(n)[2:]
        
        @cache
        def f(i:int, up_limit:bool, cnt1: int, is_num:bool):
            if i == len(sf):
                return 1 if is_num and depth[cnt1]+1 == k else 0

            hi = int(sf[i]) if up_limit else 1          
            ans = 0
            for d in range(hi+1):
                if not is_num and d == 0:
                    ans += f(i+1, up_limit and d==hi, cnt1, False)
                else:   
                    ans += f(i+1, up_limit and d==hi, cnt1 + (d==1), True)
            return ans
        return f(0, True, 0, False) - (1 if k == 1 else 0)