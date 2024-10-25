import collections

# 输入为: 1 2 3 4 5, 返回为 string
a = input()
# a = '1 2 3 4 5'
print(a)

a = input().split()
print(a)

# 输入为: 1,2,3,4,5
b = input().split(',')
print(b)


# 输入为： 输入转换为整数
a = int(input()) # 单个转换

b = input().split() # 输入为:1 2 3 4 5
c = [int(i) for i in b] # 使用列表进行批量转换 c = [1, 2, 3, 4, 5]


d = [int(i) for i in input().split()] # 当然可以一步倒位

# 使用map进行并行转换
e = map(int, input().split()) # 此时e是一个map迭代器，不能赋值，也不能索引
f = list(e) # 转换为列表，e = [1, 2, 3, 4, 5]
g = list(map(int, input().split())) # 一步到位

# input().strip()


# 多行输入，同时未指定用例的个数
while True:
    try:
        data = input()
        # solve(data) # 核心函数
    except:
        break


n = int(input()) # 获取用例个数
for _ in range(n):
	data = input()
	print(f"output {data}") # 核心函数
     
# 输出 a=1, b=2, c=3
print(a, b, c) # print默认以空格为分隔符

print(a, b, c, sep=',') # 以逗号为分隔符

res = [1,2,3]
for i in range(len(res)):
    print(res[i], end=' ')  # end的默认值是'\n'，即换行



# 定义链表结构
class ListNode:
    def __init__(self,val,next=None):
        self.val = val
        self.next = next

# 数组转链表
def nums2ListNode(nums):
    dummy = ListNode(None)
    root = ListNode(nums[0])
    dummy.next = root
    i = 1
    while i < len(nums):
        node = ListNode(nums[i])
        root.next = node
        root = root.next
        i += 1
        root.next = None
    return dummy.next

# 打印链表
nums = [1,2,3,4,5]
root = nums2ListNode(nums)
while root:
    print(root.val)
    root = root.next


# 定义二叉树类函数
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
	  

# 由数组转二叉树
def construct_binary_tree(nums, index):
    if index >= len(nums):
        return
    # -1作为空节点
    if nums[index] == -1:
        return None
    left = index * 2 + 1
    right = index * 2 + 2
    root = TreeNode(nums[index])
    root.left = construct_binary_tree(nums, left)
    root.right = construct_binary_tree(nums, right)
    return root

# 中序遍历
def inorder_traversal(root):
    if not root: return
    inorder_traversal(root.left)
    print(root.val, end=' ')
    inorder_traversal(root.right)

# 输入为 1 2 3 null 4 null 5
#      1
#    /   \
#   2     3
#    \     \
#     4     5
if __name__ == "__main__":
	nums = input().split()
	nums = [int(num) if num != 'null' else -1 for num in nums]
	root = construct_binary_tree(nums, 0)
	inorder_traversal(root)


# 数组转二叉树
def construct_binary_tree(nums):  # nums = ['1', '2', '3', 'null', 'null', 'null', '5']
    if nums == []: return
    root = TreeNode(nums[0])
    queue = collections.deque()
    queue.append(root)
    i = 1
    while i < len(nums):
        node = queue.popleft()
        if i < len(nums) and nums[i] != -1:
            node.left = TreeNode(nums[i])
            queue.append(node.left)
        i += 1
        if i < len(nums) and nums[i] != -1:
            node.right = TreeNode(nums[i])
            queue.append(node.right)
        i += 1
    return root
  
# 中序遍历
def inorder_traversal(root):
    if not root: return
    inorder_traversal(root.left)
    print(root.val, end=' ')
    inorder_traversal(root.right)
  
# 输入 1 null 1 null 1 2
#    1
#  /  \
#null  1
#    /   \
#   null  1
#        /
#       2
if __name__ == "__main__":
    nums = input().split()
    nums = [int(num) if num != 'null' else -1 for num in nums]
    root = construct_binary_tree(nums)
    inorder_traversal(root)
  	# 输出 1 1 2 1