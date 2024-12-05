from typing import List

# 周赛 371
class Solution:
    def maximumStrongPairXor(self, nums: List[int]) -> int:
        # 参考题解，从 421 复制代码并修改
        nums.sort() # 排序，前面遍历的小于后面的

        target = 0
        high = nums[-1].bit_length() - 1

        for i in range(high, -1, -1):
            target <<= 1
            newval = target + 1 # 尽量找当前位为 1
            h = dict() # key 为 高位的mask，value 为原值
            for v in nums:
                v_mask = v >> i
                # !!!太巧妙了!!!
                if v_mask ^ newval in h and h[v_mask ^ newval]*2>=v:
                    target = newval # 找到当前位为1的XOR
                    break
                h[v_mask] = v # 如果有v_mask一样的，可以直接覆盖, 为什么？
        return target