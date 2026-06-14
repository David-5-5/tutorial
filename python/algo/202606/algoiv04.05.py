from cmath import inf
from typing import Optional, Tuple

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        # 自行解答
        if not root: return True
        ans = True
        def dfs(node: Optional[TreeNode]) -> Tuple[int, int]:
            nonlocal ans
            mn = mx = node.val
            if not ans: return (mn, mx)
            if node.left:
                l_min, l_max = dfs(node.left)
                if l_max >= node.val:
                    ans = False
                mn = min(l_min, mn)
            if node.right:
                r_min, r_max = dfs(node.right)
                if r_min <= node.val:
                    ans = False
                mx = max(mx, r_max)
            return (mn, mx)
        
        dfs(root)
        return ans
    
