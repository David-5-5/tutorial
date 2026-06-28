from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def BSTSequences(self, root: Optional[TreeNode]) -> List[List[int]]:
        
        if root is None: return [[]]
        # 洗牌合并，保持左右子树的相对顺序不变
        def weave(a: List[int], b: List[int]) -> List[List[int]]:
            res = []
            path = []
            def backtrack(i, j):
                if i == len(a) and j == len(b):
                    res.append(path.copy())
                    return
                if i < len(a):
                    path.append(a[i])
                    backtrack(i+1, j)
                    path.pop()
                if j < len(b):
                    path.append(b[j])
                    backtrack(i, j+1)
                    path.pop()
            backtrack(0, 0)
            return res
        
        left = self.BSTSequences(root.left)
        right = self.BSTSequences(root.right)
        
        ans = []

        for l in left:
            for r in right:
                for mixed in weave(l, r):
                    ans.append([root.val] + mixed)

        return ans