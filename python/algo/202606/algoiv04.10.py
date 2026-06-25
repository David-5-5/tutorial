from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def checkSubTree(self, t1: Optional[TreeNode], t2: Optional[TreeNode]) -> bool:
        
        def isSame(sub1: Optional[TreeNode], sub2: Optional[TreeNode]) -> bool:
            if sub1 is None or sub2 is None:
                return sub1 is sub2
            if sub1.val != sub2.val: return False
            return isSame(sub1.left, sub2.left) and isSame(sub1.right, sub2.right)
            
        def dfs(sub: Optional[TreeNode]) -> bool:
            if sub is None: return sub is t2
            if isSame(sub, t2): return True
            if dfs(sub.left): return True
            if dfs(sub.right): return True
            return False
        
        return dfs(t1)