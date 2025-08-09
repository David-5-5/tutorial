
from functools import cache
from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 二叉树 - 2.14 链表+二叉树
class Solution:
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        
        @cache
        def dfs (cur: ListNode, node: TreeNode) -> bool:
            if cur is None: return True
            if node is None: return False
            if cur.val == node.val and (dfs(cur.next, node.left) or dfs(cur.next, node.right)):
                return True
            
            return dfs(head, node.left) or dfs(head, node.right)
