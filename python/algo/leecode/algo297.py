from common import *
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        if root is None:
            return ""
        fifo = [root]
        result = []
        while len(fifo) > 0:
            node = fifo.pop(0)
            
            if node is None:
                result.append(None)
            else:
                result.append(node.val)
            
            if node is not None:
                fifo.append(node.left)
                fifo.append(node.right)
        while result[-1] is None:
            result.pop()
        retStr = ""
        for e in result:
            if e is None:
                retStr += "null,"
            else:
                retStr += str(e) + ","
        return retStr[0:-1]
 
    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        if (len(data) == 0):return None
        l = data.split(",")
        n = len(l)
        if n == 0:
            return None
        root = TreeNode(l[0])
        cursor = 1
        fifo = [root]
        while len(fifo) > 0 and cursor < n:
            node = fifo.pop(0)
            right, left = None, None
            if l[cursor] is not None:
                left = TreeNode(l[cursor])
                fifo.append(left)
            if cursor + 1 < n and l[cursor+1] is not None:
                right = TreeNode(l[cursor+1])
                fifo.append(right)
            cursor += 2
            node.right = right
            node.left = left
    
        return root

# Your Codec object will be instantiated and called as such:
ser = Codec()
deser = Codec()
input = "1,2,3,null,null,4,5"
ans = ser.serialize(deser.deserialize(input))
print(ans)
print(ans == input)