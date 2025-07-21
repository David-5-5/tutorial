from collections import defaultdict
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 二叉树 - 2.7 回溯
class Solution:
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        cnt = defaultdict(int)
        cnt[0] = 1
        
        def dfs(node: Optional[TreeNode], sum: int) -> int:
            if node is None: return 0
            sum += node.val
            res = cnt[sum-targetSum]
            cnt[sum] += 1
            res += dfs(node.left, sum)
            res += dfs(node.right, sum)
            cnt[sum] -= 1   # 恢复现场
            return res
        
        return dfs(root, 0)
    
