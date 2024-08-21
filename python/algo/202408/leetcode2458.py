# Definition for a binary tree node.
from collections import defaultdict
from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        height = defaultdict(int) # ·每棵子树高度 key 为 node

        def get_height(node:Optional[TreeNode]):
            if node is None: return 0
            height[node] = 1 + max(get_height(node.left),get_height(node.right))
        
            return height[node]
        
        get_height(root)
        
        res = [0] * (len(height.keys())+1)
        def dfs(node:Optional[TreeNode], ph, bh):
            if node is None: return 0
            ph += 1
            res[node.val] = bh
            dfs(node.left, ph, max(bh, ph+ height[node.right]))
            dfs(node.right, ph, max(bh, ph+ height[node.left]))

        dfs(root, -1, 0)
        ans = []
        for q in queries:ans.append(res[q])
        return ans

    def treeQueries2(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        height = defaultdict(int) # ·每棵子树高度 key 为 node.val

        def get_height(node:Optional[TreeNode]):
            if node is None: return 0
            height[node.val] = 1 + max(get_height(node.left),get_height(node.right))
        
            return height[node.val]
        
        get_height(root)
        
        res = [0] * (len(height.keys())+1)
        def dfs(node:Optional[TreeNode], ph, bh):
            if node is None: return 0
            ph += 1
            res[node.val] = bh
            dfs(node.left, ph, max(bh, ph+ (height[node.right.val] if node.right else 0)))
            dfs(node.right, ph, max(bh, ph+ (height[node.left.val] if node.left else 0)))

        dfs(root, -1, 0)
        ans = []
        for q in queries:ans.append(res[q])
        return ans

if __name__ == "__main__":
    sol = Solution()
