# 位运算 - 其他
class Solution:
    def concatenatedBinary(self, n: int) -> int:
        # 自行解答
        mod = 10 ** 9 + 7
        ans = 1
        for i in range(2, n+1):
            ans <<= i.bit_length()
            ans = (ans + i) % mod
        return ans
            
