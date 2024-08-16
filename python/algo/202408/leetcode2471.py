
# Definition for a binary tree node.
from bisect import bisect_left
from typing import Optional

# 周赛 319
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        ans = 0
        q = [root]
        while q:
            prev = q
            q, vals = [], []

            for node in prev:
                vals.append(node.val)
                if node.left:   q.append(node.left)
                if node.right:  q.append(node.right)
            
            sv = sorted(vals)
            vals = [bisect_left(sv, v) for v in vals]

            for i in range(len(vals)):  
                while i != vals[i]:
                    ans += 1
                    v = vals[i] # 交换两个数组的元素，下标要赋临时变量
                    vals[i], vals[v] = vals[v], vals[i]
                    # As following code is WRONG
                    # vals[i], vals[vals[i]] = vals[vals[i]], vals[i]

        return ans

import sys
sys.path.append("./python/") # only validate when debug
from common import createTreeNode
if __name__ == "__main__":
    sol = Solution()
    root = [1,4,3,7,6,8,5,None,None,None,None,9,None,10]
    print(sol.minimumOperations(createTreeNode(root)))
