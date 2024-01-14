import sys
sys.path.append(sys.path[0] + "/../..")
from common import TreeNode, createTreeNode

class Solution:
    def minCameraCover(self, root: TreeNode) -> int:
        count = 0

        def postorder(node: TreeNode) :
            nonlocal count
            if node.left:
                postorder(node.left)
            if node.right:
                postorder(node.right)
            
            # 节点的val保持为0，表明该节点被父节点监控，父节点的val = 1，表明安装监控
            # 节点的val = -1 ，表明该节点可以被字节的监控
            # 叶子节点不要安装监控
            if (node.left is not None and node.left.val == 0) or (node.right is not None and node.right.val == 0):
                # 若左右子节点存在一个子节点未安装监控，该节点需要安装监控
                node.val = 1
                count += 1
            elif (node.left is not None and node.left.val == 1) or (node.right is not None and node.right.val == 1):
                # 若左右子节点有一个节点安装监控，且左右子节点不存在未安装监控的情况，该该节点被子节点监控
                node.val = -1
        postorder(root)
        # 根结点 val = 0，无父节点，根节点安装监控
        if root.val == 0 : count += 1
        return count


if __name__ == "__main__":
    sol = Solution()
    root = [0,0,None,0,0]
    print(sol.minCameraCover(createTreeNode(root)))