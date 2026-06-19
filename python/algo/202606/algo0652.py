from typing import List, Optional

# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def findDuplicateSubtrees(self, root: Optional[TreeNode]) -> List[Optional[TreeNode]]:
        # 用序列化方法
        repeat = set()
        seen = {}

        def dfs(node: Optional[TreeNode]) -> str:
            if node is None: return ""
            
            # 必须带级联符号 用 "#..." 或 "(...)" 或 "#....#"
            serial = str(node.val) + "#" + dfs(node.left) + "#" + dfs(node.right)
            if serial in seen:
                repeat.add(seen[serial])
            else:
                seen[serial] = node
            
            return serial
        
        dfs(root)
        return list(repeat)

