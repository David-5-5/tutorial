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


    def findMaximumXOR2(self, nums: List[int]) -> int:
        # 参考题解，方法二 0-1 字典树
        high = max(nums).bit_length() - 1
        trie = Trie(high)

        ans = 0
        for v in nums:
            trie.insert(v)
            ans = max(ans, trie.max_xor(v))
        return ans