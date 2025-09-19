# 预计算 pres 数组
from bisect import bisect_right
from functools import cache
from typing import List

# 预计算 pres 数组
mx = 46
pres = [0] * mx
pres[0] = 1  # 2^0 = 1
for i in range(1, mx):
    pres[i] = pres[i-1] * 2 + (1 << i)

class Solution:
    def findProductsOfElements(self, queries: List[List[int]]) -> List[int]:
        # 计算从 1 到 val 的所有数字的二进制表示中 1 的个数之和
        @cache
        def count(val):
            if val == 0:
                return 0
            if val == 1:
                return pres[0]
            
            e = val.bit_length() - 1
            return val - (1 << e) + 1 + count(val - (1 << e)) + pres[e-1]
        
        # 内部计算函数
        @cache
        def inner(val):
            if val == 0 or val == 1:
                return 0
            if val == 2:
                return 1
                
            e = val.bit_length() - 1
            return e * (val - (1 << e) + 1) + inner(val - (1 << e)) + inner((1 << e) - 1)
        
        # 乘法计算函数
        @cache
        def mul(val, cnt):
            n_val = val
            f_cnt = count(val)
            if cnt < f_cnt:
                n_val -= 1
                
            res = inner(n_val)
            diff = cnt - count(n_val)
            
            for _ in range(diff):
                lb = val & -val  # 获取最低位的1
                res += lb.bit_length() - 1
                val -= lb
            return res
        
        ans = []
        for q in queries:
            start, end, mod= q[0] + 1, q[1] + 1, q[2]
            
            if mod == 1:
                ans.append(0)
                continue
                
            # 查找满足条件的值
            def find_val(cnt: int) -> int:
                it_idx = bisect_right(pres, cnt)  # it_idx 对应 C++ 中 it - pres.begin() 的值
                
                if it_idx == 0 or pres[it_idx - 1] == cnt:
                    return (1 << it_idx) - 1  # 对应 C++ 的 (1 << it-pres.begin()) - 1
                
                left = (1 << it_idx) - 1
                right = (1 << (it_idx + 1))
                
                # Python 整数除法用 //，对应 C++ 的 /（整数类型）
                while left + 1 < right:
                    mid = (left + right) // 2
                    if count(mid) < cnt:
                        left = mid
                    else:
                        right = mid
                
                return right
            
            start_val = find_val(start - 1)
            end_val = find_val(end)
            
            # 计算指数并添加到结果
            exponent = mul(end_val, end) - mul(start_val, start - 1)
            ans.append(pow(2, exponent, mod))
            
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.findProductsOfElements([[169879810433127,550761388797555,99654]]))