from functools import reduce
from operator import or_
from typing import List

class XorBasis:
    # n 为值域最大值 U 的二进制长度，例如 U=1e9 时 n=30
    def __init__(self, n: int):
        self.b = [0] * n

    def insert(self, x: int) -> None:
        b = self.b
        # 从高到低遍历，保证计算 max_xor 的时候，参与 XOR 的基的最高位（或者说二进制长度）是互不相同的
        for i in range(len(b) - 1, -1, -1):
            if x >> i:  # 由于大于 i 的位都被我们异或成了 0，所以 x >> i 的结果只能是 0 或 1
                if b[i] == 0:  # x 和之前的基是线性无关的
                    b[i] = x  # 新增一个基，最高位为 i
                    return
                x ^= b[i]  # 保证每个基的二进制长度互不相同
        # 正常循环结束，此时 x=0，说明一开始的 x 可以被已有基表出，不是一个线性无关基

    def max_xor(self) -> int:
        b = self.b
        res = 0
        # 从高到低贪心：越高的位，越必须是 1
        # 由于每个位的基至多一个，所以每个位只需考虑异或一个基，若能变大，则异或之
        for i in range(len(b) - 1, -1, -1):
            if res ^ b[i] > res:  # 手写 max 更快
                res ^= b[i]
        return res

class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n, ans = len(nums), 0
        if n < 4:return sum(nums)
        full = (1 << n) - 1 
         
        full_v = (1 << max(nums).bit_length()) - 1
        for i in range(full + 1):
            and_b, xor_s = -1, 0
            if i == 0:
                and_b = 0
            for j in range(n):
                if (i >> j) & 1: and_b &= nums[j]
                else:
                    xor_s ^= nums[j]
            
            even_bits = (~xor_s) & full_v
            xor_nums = []
            for j in range(n):
                if ((i >> j) & 1) == 0:
                    if even_bits & nums[j]:
                        xor_nums.append(even_bits & nums[j])
            xor_a = 0
            # print(xor_nums)
            if len(xor_nums):
                if and_b + xor_s + 2 * reduce(or_, xor_nums) <= ans: continue
                m = max(xor_nums).bit_length()
                b = XorBasis(m)
                for x in xor_nums:
                    b.insert(x)
                
                xor_a = b.max_xor()
            if and_b + xor_s + 2 * xor_a > ans:
                ans = and_b + xor_s + 2 * xor_a
        return ans

if __name__ == "__main__":
    print(Solution().maximizeXorAndXor([902,558,609,420]))