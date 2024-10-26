# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
from typing import Optional

# 专题 链表练习
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:


        cur1, cur2, prev1, bit = l1, l2, None, 0
        while cur1 and cur2:
            cur1.val = (cur1.val + cur2.val + bit) % 10
            if cur1.val + cur2.val + bit > 9: bit = 1
            else:bit = 0
            prev1 = cur1
            cur1 = cur1.next
            cur2 = cur2.next
        
        if cur2:
            cur2.val += bit
            prev1.next = cur2

        if cur1:
            cur1.val += bit
    
        return reverse(l1)
