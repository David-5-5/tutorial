# Definition for a binary tree node.
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(node: TreeNode):
            nonlocal ans
            if node is None:return -1
            l = dfs(node.left)
            r = dfs(node.right)

            if l + r + 2 > ans: ans = l + r + 2
            return max(l, r) + 1

        dfs(root)
        return ans

