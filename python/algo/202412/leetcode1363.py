from typing import List

# 
class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        # 自行解答
        # 1. 从大到小排序，接近最大值
        digits.sort(reverse=True)

        # 整除 3 的数和也整数3
        d_sum = sum(digits)
        rem, n = d_sum % 3, len(digits)

        if rem : # 不能整除 rem 余数为 1 或 2
            # 从后遍历，尽量擅长最小的 num，num % 3 == rem
            for i in range(n-1, -1, -1):
                if digits[i] % 3 == rem:
                    digits.pop(i)
                    break
            
            if n == len(digits): # 不存在 num % 3 == rem
                # 那么一定存在两个 num % 3 == (2 * rem) % 3
                rem = rem * 2 % 3
                for i in range(n-1, -1, -1):
                    if digits[i] % 3 == rem:
                        digits.pop(i)
                        if n - 2 == len(digits):
                            break
            
        return "0" if len(digits) and sum(digits) == 0 else "".join(str(i) for i in digits)

            


        