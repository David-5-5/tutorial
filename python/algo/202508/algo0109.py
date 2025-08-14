# Definition for singly-linked list.
from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# 二叉树 - 2.14 链表+二叉树
class Solution:
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:
        def get_len(head: Optional[ListNode]) -> int:
            length = 0
            while head:
                length += 1
                head = head.next
            return length

        def convert_to_bst(left: int, right: int) -> Optional[TreeNode]:
            if left > right: return None

            mid = (left + right) >> 1   # 保持平衡
            root = TreeNode()
            root.left = convert_to_bst(left, mid-1)
            nonlocal head
            root.val = head.val         # 中序遍历第一个元素就是列表第一个元素
            head = head.next            # 以此类推
            root.right = convert_to_bst(mid+1, right)
            return root

        length = get_len(head)
        return convert_to_bst(0, length-1)
    



