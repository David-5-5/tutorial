# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

from typing import Optional 
class Solution:
    def mergeKLists(self, lists) -> Optional[ListNode]:

        while len(lists) > 1:
            merged = []
            n = len(lists)
            for i in range(n//2):
                merged.append(self.merge(lists[i], lists[n-1-i]))
            if  n%2 == 1:
                merged.append(lists[n//2])
            lists = merged 
        if len(lists) == 1:
            return lists[0]
        else:
            return None

    def merge(self, l1: Optional[ListNode], l2: Optional[ListNode])-> Optional[ListNode]:
        head = tail = ListNode(-10000)
        while l1 is not None or l2 is not None:
            if l2 is None:
                tail.next = l1
                return head.next
            if l1 is None:
                tail.next = l2
                return head.next
            if l1.val < l2.val:
                tail.next = l1
                tail = l1
                l1 = l1.next
                tail.next = None
            else:
                tail.next = l2
                tail = l2
                l2 = l2.next
                tail.next = None

if __name__ == "__main__":
    sol = Solution()
    lists = [[1,4,5],[1,3,4],[2,6]]
    print(sol.mergeKLists(lists))