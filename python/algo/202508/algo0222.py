from bisect import bisect_left
from typing import Optional
from python.common import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

# 二叉树 - 2.16 其他
class Solution:
    def countNodes(self, root: Optional[TreeNode]) -> int:
        # 从 c++ 转换过来，使用 bisect_left 库函数
        h = 0
        if root is None: return 0
        cur = root
        while cur.left is not None:
            h += 1
            cur = cur.left
        
        left, right = (1 << h) - 1, 1 << (h+1)
        def check(mid: int) -> bool:
            cur = root
            for i in range(h-1, -1, -1):
                if mid >> i & 1:
                    if cur.right is not None: cur = cur.right
                    else: return False 
                else:
                    if cur.left is not None: cur = cur.left
                    else: return False 
            return True
        left, right = (1 << h) - 1, 1 << (h+1)
        while left + 1 < right:
            mid = (left + right) >> 1
            if check(mid):
                left = mid
            else: right = mid
        return left
        # 下面库函数不正确 ???
        # return bisect_left(range(left, right), True, key=check) + left