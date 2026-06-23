from typing import List, Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def listOfDepth(self, tree: Optional[TreeNode]) -> List[Optional[ListNode]]:
        ans = []
        tail = []
        def dfs(node: Optional[TreeNode], depth: int) :
            if node is None: return

            if len(ans) == depth:
                ans.append(ListNode(node.val))
                tail.append(ans[-1])
            else:
                tail[depth].next = ListNode(node.val)
                tail[depth] = tail[depth].next
            
            dfs(node.left, depth+1)
            dfs(node.right, depth+1)


        dfs(tree, 0)

        return ans