# Definition for a binary tree node.
from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 周赛 311
class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        vals = []
        
        def bfs(node: Optional[TreeNode]) :
            q = [node]
            
            while q:
                cur = q.pop(0)
                if cur.left:
                    q.append(cur.left)
                    q.append(cur.right)
                vals.append(cur.val)
        # bfs tree to add val to array
        bfs(root)

        # reverse the val of odd level
        n = len(vals)
        revs = []
        start = 0
        for i in range(15):
            if start >= n:break
            l = 1 << i
            if i % 2 == 1:
                revs.extend(vals[start:start+l][::-1])
            else:
                revs.extend(vals[start:start+l])
            start += l
        
        def dfs(node: Optional[TreeNode], pos:int):
            node.val = revs[pos]
            if node.left:
                dfs(node.left, pos*2+1)
                dfs(node.right, pos*2+2)
        
        dfs(root, 0)

        return root