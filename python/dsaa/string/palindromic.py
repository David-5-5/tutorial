'''给定一个长度为 n 的字符串 s, 请找到所有对 (i, j) 使得子串 s[i..j] 为一个回文串. 
当 t = t_rev 时, 字符串t是一个回文串(_rev 是 t 的反转字符串)
我们找出值 d_1[i] 和 d_2[i]。二者分别表示以位置 i 为中心的长度为奇数和长度为偶数的回文串个数
'''

def navie(s: str):
    n = len(s)
    d1 = [0] * n
    d2 = [0] * n
    for i in range(n):
        d1[i] = 1
        while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
            d1[i] += 1

        d2[i] = 0
        while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
            d2[i] += 1
    res = 0
    for i in range(n):
        res += d1[i] + d2[i]
    return res


def manacher(s: str):
    '''
    1) 如果 i 位于当前子回文串之外, 即 i > r, 那么我们调用朴素算法。因此我们将连续地
    增加 d_1[i], 同时在每一步中检查当前的子串 [i - d_1[i] ... i + d_1[i]]是否为一个回文串. 
    如果我们找到了第一处对应字符不同, 又或者碰到了s的边界, 则算法停止. 在两种情况下我们均已计算
    完 d_1[i]. 此后, 仍需记得更新 (l, r)。

    2) 现在考虑 i <= r 的情况。我们将尝试从已计算过的 d_1[] 的值中获取一些信息. 首先在子回
    文串 (l, r) 中反转位置 i, 即我们得到 j = l + (r - i). 现在来考察值 d_1[j]. 因为位置
    j同位置 i 对称, 我们几乎总是 可以置 d_1[i] = d_1[j]. 当j - d1[j] < l 时,不能保证 
    
    '''
    n = len(s)
    d1 = [0] * n
    d2 = [0] * n
    l, r  = 0, -1
    for i in range(n):
        if i <= r:
            d1[i] = min(d1[l+r-i], r-i)
        while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
            d1[i] += 1
        if i + d1[i] > r:
            l, r = i - d1[i], i + d1[i]
    
    l, r  = 0, -1
    for i in range(n):
        if i <= r:
            d2[i] = min(d2[l+r-i+1], r-i)
        while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
            d2[i] += 1
        if i + d1[i] > r:
            l, r = i - d2[i]-1, i + d2[i]
    res = 0
    for i in range(n):
        res += d1[i] + d2[i]
    return res
            

s = "abbaxyzyx"
print(navie(s))
print(manacher(s))