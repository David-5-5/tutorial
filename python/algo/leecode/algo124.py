from math import inf
from common import TreeNode
from typing import Optional
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution: 
    maxPath = 0
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        stack = [root]
        self.maxPath = root.val
        left  = self.maxChild(root.left)
        right = self.maxChild(root.right)
        self.maxPath = max(self.maxPath, root.val, root.val+left, root.val+right, root.val + left + right)
        return self.maxPath
        
    def maxChild(self, node: Optional[TreeNode])-> int:
        if node is None: return 0
        if node.left is None and node.right is None:
            self.maxPath = max(self.maxPath, node.val)
            return node.val
        left  = self.maxChild(node.left)
        right = self.maxChild(node.right)
        self.maxPath = max(self.maxPath, node.val, node.val+left, node.val+right, node.val + left + right)
        return max(0, node.val, node.val+left, node.val+right)

    # 参考算法精讲23 及 543
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        ans = -inf

        def dfs(node: TreeNode):
            nonlocal ans
            if node is None:return 0
            l = dfs(node.left)
            r = dfs(node.right)

            if l + r + node.val > ans: ans = l + r + node.val
            return max(max(l, r) + node.val, 0)
        
        dfs(root)
        return ans
