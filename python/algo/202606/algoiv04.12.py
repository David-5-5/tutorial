# Definition for a binary tree node.
from collections import defaultdict
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def pathSum(self, root: Optional[TreeNode], sum: int) -> int:
        # 同 437
        cnt = defaultdict(int)
        cnt[0] = 1
        
        def dfs(node: Optional[TreeNode], val: int) -> int:
            if node is None: return 0
            val += node.val
            res = cnt[val-sum]
            cnt[val] += 1
            res += dfs(node.left, val)
            res += dfs(node.right, val)
            cnt[val] -= 1   # 恢复现场
            return res
        
        return dfs(root, 0)
            