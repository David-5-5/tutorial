# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        # 同 236
        def dfs(node: TreeNode) -> TreeNode:
            if node == None or node == p or node == q : return node
            lnode = dfs(node.left)
            rnode = dfs(node.right)
            if lnode and rnode: return node
            return lnode if lnode else rnode

        return dfs(root)        