# Definition for a binary tree node.
import sys
sys.path.append(sys.path[0] + "/../..")
import typing
from common import TreeNode, createTreeNode

def dfs(root: TreeNode) -> typing.Tuple[int,float]:
    if root is None: return (0, 0.0)
    lf, ls = dfs(root.left)
    rf, rs = dfs(root.right)

    return  (lf + rf + root.val, root.val + max(max(ls, rs), (lf + rf) / 2))


class Solution:

    def minimalExecTime(self, root: TreeNode) -> float:
        f,s = dfs(root)
        return s

    def minimalExecTime2(self, root):
        """
        :type root: TreeNode
        :rtype: float
        """
        def dfs(root):
            if root is None:
                return 0., 0.
            tc = root.val
			
            # 先递归左右子树
            a, b = dfs(root.left)
            c, d = dfs(root.right)
            
            tc = tc + a + c
            # 只考虑 a >= c 的情况，不满足就交换
            if a < c:
                a, c = c, a
                b, d = d, b
            
            if a - 2 * b <= c:
                pc = (a + c) / 2
            else:
                pc = c + b

            return tc, pc

        tc, pc = dfs(root)
        return tc - pc


if __name__ == "__main__":
    sol = Solution()
    # nums = [7,5,6,4]
    l1 = [1,3,3,None,None,4,4]

    root = createTreeNode(l1)
    print(sol.minimalExecTime2(root))