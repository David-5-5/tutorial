from functools import lru_cache
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 解题思路，树状DP
# 思维盲点：当灯为 close 的时候，当前不操作，进入子树
#         当灯为 open  的时候，1 + 选择1,2,3 任一开关的最小值
# 满足答案的思路：
#       当灯为 close 的时候，操作偶数次开关，0次，操作 12，13, 23开关
#       当灯为 open  的时候，操作奇数次开关，操作1,2,3，123 任一开关的最小值及 
# 
# 注，答案中 开关2,3弄反了，不过不影响结果
class Solution:
    def closeLampInTree(self, root: TreeNode) -> int:

        @lru_cache(maxsize = None)
        def dfs(cur:TreeNode, s2:int, s3:int):

            if not cur: return 0
            # if s2,s3 = 0 val does not change
            # if s2,s3 = 1 val which change state 0->1, 1->0
            val = (cur.val ^ s2) ^ s3
            if val == 0:
                res0 = dfs(cur.left, 0, s3) + dfs(cur.right,0, s3)
                res12 = dfs(cur.left, 1, s3) + dfs(cur.right, 1, s3) + 2
                res13 = dfs(cur.left, 0, s3^1) + dfs(cur.right, 0, s3^1) + 2
                res23 = dfs(cur.left, 1, s3^1) + dfs(cur.right, 1, s3^1) + 2
                return min(res0,res12,res13,res23)
            else:
                res1 = 1 + min(dfs(cur.left, 0, s3) + dfs(cur.right,0,s3), # s1
                              dfs(cur.left, 1, s3) + dfs(cur.right,1,s3), # s2
                              dfs(cur.left, 0, s3^1) + dfs(cur.right,0,s3^1)# s3
                              )
                res123 = dfs(cur.left, 1, s3^1) + dfs(cur.right, 1, s3^1) + 3
                return min(res1, res123)
        return dfs(root,0,0)