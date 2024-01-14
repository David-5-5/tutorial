# Definition for a binary tree node.
import sys
sys.path.append(sys.path[0] + "/../..")
from common import TreeNode, createTreeNode
from typing import Optional
from functools import lru_cache
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def getMaxLayerSum(self, root: Optional[TreeNode]) -> int:
        # The prefix_sum is 2-dimension array
        # row of prefix_sum is depth of tree, from 0, 1,
        # The element of (prefix_sum, left, right) 
        # left  下层节点的左节点在prefix_sum[depth+1]中的index， 若无左节点， 为-1
        # right 下层节点的右节点在prefix_sum[depth+1]中的index， 若无右节点， 为-1
        prefix_sum = []
        # 可以删除的节点： 条件满足 left==-1 或 right==-1
        remove_list = []

        # Binary tree pre-order traversal
        # 后续遍历，生成prefix_sum 及 remove_list
        def post_order(cur : Optional[TreeNode], depth: int):
            # depth 为当前节点的层次数， 根节点为 0
            left, right = -1, -1
            if cur.left is not None:
                left = post_order(cur.left, depth+1)
            if cur.right is not None:
                right = post_order(cur.right, depth+1)
            
            # The last depth
            while depth >= len(prefix_sum):
                prefix_sum.append([])
            
            p_sum = 0 if len(prefix_sum[depth]) == 0 else prefix_sum[depth][-1][0]
            # 当前节点的在 prefix_sum[depth] 中index
            inx = len(prefix_sum[depth])
            # 求前缀和
            prefix_sum[depth].append((p_sum + cur.val, left, right))
            if left==-1 or right==-1:
                remove_list.append((depth, inx))
            # 返回当前节点的在 prefix_sum[depth] 中index
            return inx

        post_order(root, 0)
        depth = len(prefix_sum)
        
        # 计算未删除节点的当前最大值
        ans = - float("inf")
        for i in range(depth):
            ans = max(ans, prefix_sum[i][-1][0])

        @lru_cache(maxsize = None)
        def remove(depth, left, right):
            nonlocal ans
            child_left, child_right = -1, -1
            # 删除所在层的 left 和 right 之间的和
            sub = prefix_sum[depth][right][0] - (0 if left == 0 else prefix_sum[depth][left-1][0])
            
            # 下层的左右节点为，当前层的 left 和 right 之间所有节点的下层的 left 和 right， 忽略不存在的节点其值为 -1
            candiate = []
            for i in range(left, right+1):
                if prefix_sum[depth][i][1] != -1: candiate.append(prefix_sum[depth][i][1])
                if prefix_sum[depth][i][2] != -1: candiate.append(prefix_sum[depth][i][2])
            if len(candiate) > 0:
                child_left = min(candiate) # 最小值即为最右节点
                child_right = max(candiate) # 最大值即为最右节点
                # 增加下一层的 child_left 和 child_right 之间的和
                add = prefix_sum[depth+1][child_right][0] - (0 if child_left == 0 else prefix_sum[depth+1][child_left-1][0])
            else:
                add = 0

            # 若删除整个层，无意义。 删除整层的条件：
            # 1） 子节点层无 child_right 及 child_right 都为-1 ，
            # 2） 左右节点间的数量等于该层的数量len(prefix_sum[depth]))
            if not (child_left + child_right == -2 and right - left + 1 == len(prefix_sum[depth])): 
                ans = max(ans, prefix_sum[depth][-1][0]-sub+add)

            # 递归调用下层
            if child_left + child_right != -2:
                remove(depth+1, child_left, child_right)
        
        # 遍历各可删除节点并重新计算各层的最大值
        for dth, inx in remove_list:
            remove(dth, inx, inx)

        return ans


if __name__ == "__main__":
    sol = Solution()
    root = [6,0,3,None,8]
    root = [1,0,-5,3,None,None,4,-1,None,None,6,4,-2]
    root = [-3,0,-5,-3,None,None,-4,-1,None,None,-6,-4]
    root = [6,7,3,6,None,2,None,5,4,99,None,100,50,None,None,1]
    root = [-2354,-6910,None,-1788,-3394,-2605,None,-459,-6928,None,-1217,-5683,-9369]

    print(sol.getMaxLayerSum(createTreeNode(root)))
