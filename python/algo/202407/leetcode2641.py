# Definition for a binary tree node.
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # 两次遍历，一次遍历计算各层的和
        # 第二次遍历在父节点处更改子结点的值，其值为用子结点所在层的和(第一次遍历的求和结果)
        # 减去父节点的两个子结点节点的和

        lsum = []
        
        def dfs1(node: TreeNode, l:int):
            if l < len(lsum):
                lsum[l] += node.val
            else:
                lsum.append(node.val)
            if node.left:
                dfs1(node.left, l+1)
            if node.right:
                dfs1(node.right, l+1)
        
        dfs1(root, 0)

        def dfs2(node: TreeNode, l:int):
            children = (node.left.val if node.left else 0) + (node.right.val if node.right else 0)
            if node.left:
                node.left.val = lsum[l+1] - children
                dfs2(node.left, l+1)
            if node.right:
                node.right.val = lsum[l+1] - children
                dfs2(node.right, l+1)

        root.val = 0
        dfs2(root, 0)
        return root