# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def inorderSuccessor(self, root: TreeNode, p: TreeNode) -> TreeNode:
        
        pre = None
        def dfs(node: TreeNode) -> TreeNode:
            nonlocal pre
            if node.left:
                cur = dfs(node.left)
                if cur != None: return cur
            if pre == p: return node
            else: pre = node
            if node.right:
                cur = dfs(node.right)
                if cur != None: return cur
            
            return None

        return dfs(root)
