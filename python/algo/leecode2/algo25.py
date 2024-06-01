from typing import Optional
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# 翻转链表 Reverse Nodes
# 关键节点说明，
# dummy 哨兵节点，对于头节点会变更的节点
# P0 是需要 k-group 翻转节点的每组节点的前一组的最后节点，起始为哨兵节点
# Pre 是前一个节点, 每组翻转的起始为 None
# cur 初始情况是当前节点每组节点的起始，不断向后遍历
class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        n, cur = 0, head
        while cur:
            cur = cur.next
            n += 1
        dummy = ListNode(next=head)
        p0 = dummy
        pre = None
        cur = p0.next
        while n >= k:
            n -= k
            for _ in range(k):
                nxt = cur.next
                cur.next = pre
                pre = cur
                cur = nxt
            
            nxt = p0.next
            p0.next.next = cur
            p0.next = pre
            p0 = nxt
        return dummy.next