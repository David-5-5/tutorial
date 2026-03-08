from typing import List

# ==================== KMP ====================
def kmp(str: str, pat: str) -> List[int]:
    n, m = len(str), len(pat)
    p_pi = [0] * m  # Prefix function
    
    # Construct prefix function
    for i in range(1, m):
        j = p_pi[i-1]
        while j > 0 and pat[j] != pat[i]:
            j = p_pi[j-1]
        if pat[j] == pat[i]:
            p_pi[i] = j + 1
        else:
            p_pi[i] = j
    
    # match the string
    ans = []
    j = 0  # pointer of patten
    for i in range(n):  # pointer of match string
        while j > 0 and str[i] != pat[j]:
            j = p_pi[j-1]
        if str[i] == pat[j]:
            j += 1
        # matched
        if j == m:
            ans.append(i - j + 1)   # index of matched string
            j = p_pi[j-1]           # pointer of patten for next
    
    return ans

# ==================== Z函数（原始思路版） ====================
def zFunc_ori(text: str) -> List[int]:
    n = len(text)
    l, r = 0, 0
    z = [0] * n
    
    for i in range(1, n):
        if i <= r:
            # z[i] = min(z[i-l], r-i+1)
            if z[i-l] < r - i + 1:
                z[i] = z[i-l]
            else:
                cur = r - i + 1
                while cur + i < n and text[cur] == text[cur + i]:
                    cur += 1
                z[i] = cur
        else:
            # brute match
            cur = 0
            while cur + i < n and text[cur] == text[cur + i]:
                cur += 1
            z[i] = cur
        
        # 更新 [l, r] 区间
        if z[i] + i - 1 > r:
            l = i
            r = z[i] + i - 1
    
    return z

# ==================== Z function ====================
def zFunc(text: str) -> List[int]:
    n = len(text)
    l, r = 0, 0
    z = [0] * n
    
    for i in range(1, n):
        if i <= r and z[i-l] < r - i + 1:
            z[i] = z[i-l]
        else:
            # 初始化z[i]，i>r则为0，否则为r-i+1
            z[i] = max(0, r - i + 1)
            # 扩展匹配长度
            while z[i] + i < n and text[z[i]] == text[z[i] + i]:
                z[i] += 1
        
        # 更新 [l, r] 区间
        if z[i] + i - 1 > r:
            l = i
            r = z[i] + i - 1
    
    return z

# ==================== Rabin-Karp算法 ====================
def rabinKarp(text: str, patten: str) -> List[int]:
    result = []
    n, m = len(text), len(patten)
    if m == 0 or n < m:
        return result
    
    mod1 = 10**9 + 7
    mod2 = 10**9 + 9
    base1 = 401
    base2 = 701
    bm1 = 1  # base1^(m-1) mod mod1
    bm2 = 1  # base2^(m-1) mod mod2
    
    # 计算base的m-1次方（预处理）
    for _ in range(m-1):
        bm1 = (bm1 * base1) % mod1
        bm2 = (bm2 * base2) % mod2
    
    # 计算初始窗口（前m个字符）和模式串的哈希值
    t1, t2 = 0, 0  # 文本串哈希
    p1, p2 = 0, 0  # 模式串哈希
    for i in range(m):
        t1 = (t1 * base1 + ord(text[i])) % mod1
        t2 = (t2 * base2 + ord(text[i])) % mod2
        p1 = (p1 * base1 + ord(patten[i])) % mod1
        p2 = (p2 * base2 + ord(patten[i])) % mod2
    
    # 检查初始窗口
    if t1 == p1 and t2 == p2:
        result.append(0)
    
    # 滑动窗口
    for i in range(m, n):
        # 移除窗口左侧字符的贡献
        t1 = (t1 + mod1 - (ord(text[i-m]) * bm1) % mod1) % mod1
        # 加入窗口右侧新字符的贡献
        t1 = (t1 * base1 + ord(text[i])) % mod1
        
        # 同理处理第二个哈希
        t2 = (t2 + mod2 - (ord(text[i-m]) * bm2) % mod2) % mod2
        t2 = (t2 * base2 + ord(text[i])) % mod2
        
        # 双哈希匹配（降低碰撞概率）
        if t1 == p1 and t2 == p2:
            result.append(i - m + 1)
    
    return result

