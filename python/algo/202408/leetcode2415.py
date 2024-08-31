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
        # 自行解答
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

    def reverseOddLevels2(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # 参考题解，方法一 :BFS
        q, level = [root], 0
        while q:
            cur = q
            q = []
            if level % 2 == 1:
                n = len(cur)
                for i in range(n // 2):
                    cur[i].val, cur[n-1-i].val = cur[n-1-i].val, cur[i].val
            
            while cur:
                node = cur.pop(0)
                if node.left:
                    q.append(node.left)
                    q.append(node.right)
            
            level ^= 1

        return root
    

    def reverseOddLevels3(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # 参考题解，方法二: DFS
        # refer to leetcode 101 对称二叉树
        
        def dfs(node1: TreeNode, node2: TreeNode, is_odd: bool) :
            if not node1: return
            if is_odd: node1.val, node2.val = node2.val, node1.val
            
            dfs(node1.left, node2.right, not is_odd)
            dfs(node1.right, node2.left, not is_odd)

            
        dfs(root.left, root.right, True)

        return root    
    