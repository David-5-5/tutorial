class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def createTreeNode(values:list) -> TreeNode:
    n = len(values)
    if n == 0:
        return None
    root = TreeNode(values[0])
    cursor = 1
    fifo = [root]
    while len(fifo) > 0 and cursor < n:
        node = fifo[0]
        del(fifo[0])
        right, left = None, None
        if values[cursor] is not None:
            left = TreeNode(values[cursor])
            fifo.append(left)
        if cursor + 1 < n and values[cursor+1] is not None:
            right = TreeNode(values[cursor+1])
            fifo.append(right)
        cursor += 2
        node.right = right
        node.left = left
 
    return root

if __name__ == "__main__":
    createTreeNode([3,5,1,6,2,0,8,None,None,7,4])
