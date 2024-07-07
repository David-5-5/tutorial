from math import gcd
from typing import List

# 举例 a0～a8, k = 3
# a0a1a2 = a1a2a3 = a2a3a4 = a3a4a5 = a4a5a6 = a5a6a7 = a6a7a8
# a0 = a3 = a6, a1 = a4 = a7, a2 = a5 = a8
# a[i] = a[i+k] = ... + a[i+jk]
# 考虑到循环的情况
# 使用裴蜀定理:
# 设 a,b 是不全为零的整数，对任意整数 x,y，满足  gcd(a,b) | ax+by
# a[i] = a[i+k] = a[i+2k] = ... = a[i+xk] = ... = a[i+xk+yn] 注+yn 表示支持循环
# gcd(k, n) | xk + yn
# xk + yn = t * gcd(k, n)
# 若 k = 3, n = 5, d=1, 即 a[0] = a[1] = ... a[n-1],都相等
class Solution:
    def makeSubKSumEqual(self, arr: List[int], k: int) -> int:
        n = len(arr)
        d = gcd(n, k)
        ans = 0
        for i in range(d):
            child = sorted(arr[i::d])
            # 和中位数的差是最小调整量
            mid = child[len(child)//2]
            for v in child:
                ans += abs(v - mid)
        return ans

if __name__ == "__main__":
    sol = Solution()
    arr, k = [2,5,5,7], 3
    print(sol.makeSubKSumEqual(arr, k))