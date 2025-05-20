from functools import cache
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 动态规划 - 12.2 树上最大独立集
class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:
        # 自行解答        
        @cache
        def dfs(node:Optional[TreeNode], f:bool) ->int:
            if node is None: return 0

            res = dfs(node.left, False) + dfs(node.right, False)
            if (not f):
                res = max(res, node.val + dfs(node.left, True) + dfs(node.right, True))
            return res

        return dfs(root, False)