'''
Z函数的朴素算法复杂度O(n2)
'''

def z_function_naive(s):
    n = len(s)
    z = [0] * n
    for i in range(1, n):
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
    return z

'''
线性算法其关键在于, 运用自动机的思想寻找限制条件下的状态转移函数, 使得可以借助之前的状态来加速计算新的状态。
在该算法中, 我们从 1 到 n-1 顺次计算 z[i] 的值(z[0]=0)。在计算 z[i] 的过程中, 我们会利用已经计算好的 z[0],\ldots,z[i-1]。
对于 i, 我们称区间 [i,i+z[i]-1] 是 i 的 匹配段, 也可以叫 Z-box。

算法的过程中我们维护右端点最靠右的匹配段。为了方便, 记作 [l,r]。根据定义, s[l,r] 是 s 的前缀。
在计算 z[i] 时我们保证 l <= i。初始时 l=r=0。

在计算 z[i] 的过程中：
1. 如果 i <= r, 那么根据 [l,r] 的定义有 s[i,r] = s[i-l,r-l], 因此 z[i] >= min(z[i-l],r-i+1)。这时：
    1.1. 若 z[i-l] < r-i+1, 则 z[i] = z[i-l]。
    1.2. 否则 z[i-l] >= r-i+1, 这时我们令 z[i] = r-i+1, 然后暴力枚举下一个字符扩展 z[i] 直到不能扩展为止。
2. 如果 i>r, 那么我们直接按照朴素算法, 从 s[i] 开始比较, 暴力求出 z[i]。
3. 在求出 z[i] 后, 如果 i+z[i]-1>r, 我们就需要更新 [l,r], 即令 l=i, r=i+z[i]-1。
'''
def z_function(s):
    n = len(s)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i <= r and z[i - l] < r - i + 1:
            z[i] = z[i - l]
        else:
            # naive算法
            z[i] = max(0, r - i + 1)
            while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    return z


s = "aaaaa"
print(z_function(s))

s = "aaabaab"
print(z_function(s))

s = "abacaba"
print(z_function(s))

