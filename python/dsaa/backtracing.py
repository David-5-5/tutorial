from typing import List

# back tracing
# 回溯的引入，为什么需要回溯？
# 举例，生成长度为2字母字符串的组合
#   letter = ['a','b',...,'z']
#   ans = []
#   for l1 in letter:
#       ret = l1
#       for l2 in letter:
#           ret += l2
#       ans.append(ret)
# 如果需要生成长度为3,4,..甚至更长的字符串组合呢？
# 
# 原问题 -> 子问题，生成长度为 n 的字符串组合，首先枚举 1 个字母，接下来在枚举剩余的 n-1 个字符串
# 使用递归完成长度为 n 的字符串组合
# 
# 回溯是使用递归完成增量构造答案的过程
# 
# 回溯三问：
# 1 当前操作 2 子问题 3 下一个子问题
# 对于回溯中递归参数 i 不是第 i 个而是大于等于 i 的部分
# dfs(i) -> dfs(i+1)

# 一般的模板
def backtracing(n:int, enums):
    ans = []
    path = [''] * n

    def dfs(i):
        if i == n:
            ans.append(''.join(path))
            return
        for c in enums:
            path[i] = c
            dfs(i+1)

    dfs(0)
    return ans

# 子集型回溯:
# 模板一，从输入的角度，每个元素 选/不选
def subset_1(nums:List[int]):
    ans = []
    path = []
    n = len(nums)

    def dfs(i):
        if i == n:
            ans.append(path.copy())
            return
        # 不选
        dfs(i+1)
        
        # 选
        path.append(nums[i])
        dfs(i+1)
        path.pop() # 恢复现场，回溯

    dfs(0)
    return ans

# 模板二，从答案的角度，每次都选一个元素，由于长度没有限制，
# 每次递归path都是一个答案
def subset_2(nums:List[int]):
    ans = []
    path = []
    n = len(nums)

    def dfs(i):
        ans.append(path.copy())
        if i == n:
            return
        
        for j in range(i,n):
            path.append(nums[j])
            dfs(j+1)
            path.pop() # 恢复现场，回溯

    dfs(0)
    return ans