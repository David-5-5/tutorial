from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# 周赛 358
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # 自行解答
        # 数字乘 2，前面的每位仅能影响前一位加1,但不会影响到更前的位置。
        #  类如 49 * 2，69 * 2，4,6决定时候进位，9进位法到前一位，但不会影响到前前一位
        # 但是这种方法不通用，当乘以更大的数
        # 79 * 9, 7 进位法 6, 余 3, 9 * 9 ，8 + 3 11, 6还需要加，影响到前前一位，需要保留更多位指针

        cur, prev = head, None
        while cur:
            if cur.val * 2 >= 10: # 需要进位
                if cur == head:
                    node = ListNode(1, head)
                    head = node
                else:
                    prev.val += 1
                cur.val = cur.val * 2 % 10
            else:
                cur.val = cur.val * 2
            prev = cur
            cur = prev.next

        return head

        # 题解的写法，简洁很多
        # if head.val > 4:
        #     head = ListNode(0, head)
        # cur = head
        # while cur:
        #     cur.val = cur.val * 2 % 10
        #     if cur.next and cur.next.val > 4:
        #         cur.val += 1
        #     cur = cur.next
        # return head
