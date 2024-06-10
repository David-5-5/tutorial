# 对于数组 a，定义其差分数组（difference array）为
# d[i] = a[i]-a[i-1], i >= 1
# d[i] = a[0]       , i = 0
# 性质 1：从左到右累加 d 中的元素，可以得到数组 a。
# 性质 2：如下两个操作是等价的:
#   区间操作 把 a 的子数组 a[i],a[i+1],.., a[j] 都加上 x
#   单点操作 把 d[i]增加x  d[j+1]减少 x，特别的，当 j+1=n, 则只需把 d[i]增加 x
# 利用性质 2，我们只需要 𝑂(1)的时间就可以完成数组 a 上的区间操作。最后利用性质 1 从差分数组复原出数组 a。



from typing import List

# 你有一个长为 n 的数组 a，一开始所有元素均为 0。
# 给定一些区间操作，其中 queries[i] = [left, right, x]，
# 你需要把子数组 a[left], a[left+1], ... a[right] 都加上 x。
# 返回所有操作执行完后的数组 a。
def solve(n: int, queries: List[List[int]]) -> List[int]:
    diff = [0] * n  # 差分数组
    for left, right, x in queries:
        diff[left] += x
        if right + 1 < n:
            diff[right + 1] -= x
    for i in range(1, n):
        diff[i] += diff[i - 1]  # 直接在差分数组上复原数组 a
    return diff
