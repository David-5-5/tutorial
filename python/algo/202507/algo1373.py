from cmath import inf
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 二叉树 - 2.9 二叉搜索树
class Solution:
    def maxSumBST(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(node : Optional[TreeNode]) -> tuple[int, int, int]:
            if node is None: return inf, -inf, 0  # 恒满足为平衡子树  
            l_mn, l_mx, l_sum = dfs(node.left)
            r_mn, r_mx, r_sum = dfs(node.right)
            nonlocal ans
            mn, mx, sum = -inf, inf, 0            # 恒不满足为平衡子树  
            if node.val>l_mx and node.val<r_mn:
                mn, mx, sum = min(l_mn, node.val), max(r_mx, node.val), l_sum + node.val + r_sum
            ans = max(ans, sum)
            return mn, mx, sum
        dfs(root)
        return ans