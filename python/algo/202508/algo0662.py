from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 二叉树 - 2.13 二叉树 BFS
class Solution:
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        max_width = 1
        # 存储当前层节点和对应的索引
        current_nodes = [root]
        current_indices = [0]
        
        while current_nodes:
            # 计算当前层宽度（只有当节点数大于1时才需要更新）
            if len(current_indices) > 1:
                current_width = current_indices[-1] - current_indices[0] + 1
                if current_width > max_width:
                    max_width = current_width
            
            # 准备下一层的节点和索引
            next_nodes = []
            next_indices = []
            
            # 遍历当前层节点，记录下一层节点及其索引
            for i in range(len(current_nodes)):
                node = current_nodes[i]
                idx = current_indices[i]
                
                # 左子节点索引：2*idx + 1
                if node.left:
                    next_nodes.append(node.left)
                    next_indices.append(idx * 2 + 1)
                
                # 右子节点索引：2*idx + 2
                if node.right:
                    next_nodes.append(node.right)
                    next_indices.append(idx * 2 + 2)
            
            # 移动到下一层
            current_nodes = next_nodes
            current_indices = next_indices
        
        return max_width