from typing import List

# The Trie class
class Node:
    __slots__ = 'children', 'cnt'

    def __init__(self):
        self.children = [None, None]
        self.cnt = 0  # 子树大小

class Trie:
    # 0-1 字典树
    def __init__(self, h:int):
        self.root = Node()
        self.HIGH_BIT = h
    
    def insert(self, v:int):
        cur = self.root
        cur.cnt += 1
        for i in range(self.HIGH_BIT, -1, -1):
            if cur.children[v>>i&1] is None:
                cur.children[v>>i&1] = Node()
            cur = cur.children[v>>i&1]
            cur.cnt += 1
    
    def remove(self, v:int):
        cur = self.root
        cur.cnt -= 1
        for i in range(self.HIGH_BIT, -1, -1):
            cur = cur.children[v>>i&1]
            cur.cnt -= 1
    
    # 求异或最大值
    def max_xor(self, y:int) -> int:
        ans = 0
        cur = self.root
        for i in range(self.HIGH_BIT, -1, -1):
            mask = y>>i & 1
            if cur.children[mask^1] is not None and cur.children[mask^1].cnt != 0:
                ans |= 1 << i
                cur = cur.children[mask^1]
            else: cur = cur.children[mask]
        return ans

# 周赛 371
class Solution:
    def maximumStrongPairXor(self, nums: List[int]) -> int:
        # 参考题解，哈希 从 421 复制代码并修改
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


    def maximumStrongPairXor2(self, nums: List[int]) -> int:
        # 参考题解，0-1 Trie
        nums.sort() # 排序，前面遍历的小于后面的
        
        trie = Trie(nums[-1].bit_length() - 1)

        ans = l = 0
        # 滑动窗口 满足 |x-y| <= min(x,y) 导出 2x >= y
        for v in nums:
            while nums[l] * 2 < v:
                trie.remove(nums[l])
                l += 1
            trie.insert(v)
            ans = max(ans, trie.max_xor(v))
        
        return ans