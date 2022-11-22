from common import *

class Solution:
    found = 0
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if root.val == p.val or root.val == q.val: found += 1
        cur = self.found
        if self.found == 2: return root

        node = self.lowestCommonAncestor(root.left, p, q)
        if found - cur == 2:
            return node
        node = self.lowestCommonAncestor(root.right, p, q)
        if found - cur == 2:
            return node

        return root




if __name__ == "__main__":
    sol = Solution()
    #input 
    print(sol.lowestCommonAncestor("bbtablud"))
