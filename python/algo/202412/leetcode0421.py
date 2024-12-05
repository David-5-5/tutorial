from typing import List

# base for 2935
class Solution:
    def findMaximumXOR(self, nums: List[int]) -> int:
        # 参考题解 方法一 哈希表 + 两数之和(异或和)
        target = 0
        high = max(nums).bit_length() - 1

        for i in range(high, -1, -1):
            target <<= 1
            newval = target + 1 # 尽量找当前位为 1
            h = set() # replace dict
            for v in nums:
                v >>= i
                if v ^ newval in h:
                    target = newval # 找到当前位为1的XOR
                    break
                h.add(v)
        return target