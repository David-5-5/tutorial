import sys
from cmath import inf
sys.path.append(sys.path[0] + "/../..")
from common import TreeNode, createTreeNode
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def minCameraCover(self, root: TreeNode) -> int:
        # 自行解答，后续遍历，在必要的情况下安装摄像头，这样保证摄像头的数量最少
        count = 0

        def postorder(node: TreeNode) :
            nonlocal count
            if node.left:
                postorder(node.left)
            if node.right:
                postorder(node.right)
            
            # 节点的val保持为0，表明该节点被父节点监控，父节点的val = 1，表明安装监控
            # 节点的val = -1 ，表明该节点可以被子节点的监控
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
    
    def minCameraCover2(self, root: TreeNode) -> int:
        # 参考视频题解，算法精讲
        
        # 状态转移 每个节点返回的值表示 在三个状态下 结点安装节点, 由子节点监控, 由父节点监控下的数量
        # 空节点： 三个状体的返回值 为 inf, 0, 0 其中空节点 安装摄像头不合法，返回无穷大，
        # 每个节点，获取左右子节点的三个值后。
        # 安装摄像头 加左右子节点的最小值 并 +1
        # 由子节点监控，加左右安装至少一个安装摄像头的最小值
        # 由父节点间监控，加左右子节点的最小值(除由父节点间监控状态)
        
        def dfs(node: TreeNode) -> tuple[int, int, int] :
            if node is None:
                return inf, 0, 0
            l_ch, l_by_fa, l_by_ch = dfs(node.left)
            r_ch, r_by_fa, r_by_children = dfs(node.right)

            choose = 1 + min(l_ch, l_by_fa, l_by_ch) + min(r_ch, r_by_fa, r_by_children)
            by_father = min(l_ch, l_by_ch) + min(r_ch, r_by_children)
            by_children = min(l_ch + min(r_ch, r_by_children), r_ch + min(l_ch, l_by_ch))

            return choose, by_father, by_children


        # 根节点无父节点，最后根节点
        choose, _, by_children = dfs(root)
        return min(choose, by_children)

if __name__ == "__main__":
    sol = Solution()
    root = [0,0,None,0,None,0,None,None,0]
    print(sol.minCameraCover(createTreeNode(root)))
    print(sol.minCameraCover2(createTreeNode(root)))