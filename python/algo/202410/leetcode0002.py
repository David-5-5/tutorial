# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
from typing import Optional

# 专题 链表练习
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        # 自行解答
        cur1, cur2, prev1, bit = l1, l2, None, 0
        while cur1 and cur2:
            val = cur1.val + cur2.val + bit
            bit = val // 10
            cur1.val = val % 10
            prev1 = cur1
            cur1 = cur1.next
            cur2 = cur2.next
        
        if cur2: tail = cur2
        else: tail = cur1

        if tail:
            prev1.next = tail
            while bit:
                val = tail.val + bit
                bit = val // 10
                tail.val = val % 10
                if bit and tail.next:
                    tail = tail.next
                elif bit:
                    node = ListNode(bit)
                    tail.next = node
                    break
        elif bit:
            node = ListNode(bit)
            prev1.next = node

        return l1