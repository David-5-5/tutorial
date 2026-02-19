from typing import Optional

# Definition for singly-linked list.
# 同 19
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:

        tail = head
        nth = head
        prev = None
        cur = 0
        while (tail.next is not None):
            if (cur >= n - 1):
                prev = nth
                nth = nth.next
            tail = tail.next
            cur += 1
        if prev is None:
            return head.next
        else:
            prev.next = nth.next
        return head