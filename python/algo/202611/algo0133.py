from typing import Optional


# Definition for a Node.
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        vis = {}

        def dfs(node: Optional['Node']) -> Optional['Node']:
            if node in vis: return vis[node]
            nnode = None(node.val)
            vis[node] = nnode
            for nb in node.neighbors:
                nnode.neighbors.append(dfs(nb))

            return nnode
        return dfs(node)
