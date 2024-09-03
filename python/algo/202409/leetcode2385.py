# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
from typing import Optional

# 周赛 307
class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        # 参考题解
        # 先使用 DFS 找到节点的根节点
        parent = {}
        start_node = None
        def dfs(node: Optional[TreeNode], pa: Optional[TreeNode]):
            if node is None: return
            nonlocal start_node
            parent[node] = pa

            if node.val == start:
                start_node = node

            dfs(node.left, node)
            dfs(node.right, node)
        dfs(root, None)
        
        # bfs 从 start_node节点出发，进行父节点，子节点的广度遍历
        q = [start_node]
        vis = {start_node, None}
        ans = -1
        while q:
            ans += 1
            tmp = q
            q = []
            for node in tmp:
                for x in [node.left, node.right, parent[node]]:
                    if x not in vis:
                        q.append(x)
                        vis.add(x)

        return ans