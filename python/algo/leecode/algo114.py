from common import TreeNode
from typing import Optional
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        if root is None: return
        stack = []
        self.addToStack(root,stack)
        for i in range(len(stack)-1):
            stack[i].left = None
            stack[i].right = stack[i+1]
        
    def addToStack(self, node: Optional[TreeNode], stack):
        if node is None:return
        stack.append(node)
        self.addToStack(node.left, stack)
        self.addToStack(node.right, stack)
