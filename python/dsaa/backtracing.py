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
# 回溯三问：
# 1 当前操作 2 子问题 3 下一个子问题
# 对于回溯中递归参数 i 不是第 i 个而是大于等于 i 的部分
# dfs(i) -> dfs(i+1)
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

# 组合型回溯: 与子集型回溯相似，它同样也会涉及元素的选与不选，不同的是组合型回溯
# 需要增加判断条件来满足题意，达到剪枝优化的目的
def combine_1(n:int, k:int):
    ans = []
    path = [] # [0] * k , k 表示组合的数量

    def dfs(i):
        d = k - len(path)
        if i < d:                       # 剪枝，根据题意
            return
        if len(path) == k:              # 边界条件
            ans.append(path.copy())
            return
        for j in range(i,0,-1):
            path.append(j)
            dfs(i-1)
            path.pop()
    dfs(n)
    return ans


# 排列型回溯，相比较组合型回溯(1,2)(2,1)是相同的结果，
# 排列型回溯需要对下一个子问题给出可选列表
# dfs(i,s) -> dfs(i+1, s-{xi1})
#          -> dfs(i+1, s-{xi2})
#              ...  ... ...
#          -> dfs(i+1, s-{xik})
def premute(nums:List[int]):
    n = len(nums)
    ans = []
    path = [0] * n # [] , n 表示组合的数量

    def dfs(i,s):
        if i == n:              # 边界条件
            ans.append(path.copy())
            return
        for x in s:
            path[i] = x
            dfs(i+1,s-{x})

    dfs(0, set(nums))
    return ans