# 判断半回文
from functools import cache
from math import inf


def isHalfPalindrome(tt:str) -> bool:
    if len(tt) < 2: return False
    l, max_d = len(tt), len(tt) // 2
    
    def isPalindrome(sub:str) -> bool:
        l = len(sub)
        return sub[0:l//2] == sub[(l+l%2)//2:]

    for d in range(max_d, 0, -1):
        if l % d == 0 and all(isPalindrome(tt[o::d]) for o in range(d)):
            return True
    return False

# 参考题解，优化
# 预处理200及以下的所有整数的因子
MX = 201
divisors = [[] for _ in range(MX)]
for i in range(1, MX):
    for j in range(i * 2, MX, i):
        divisors[j].append(i)

# 半回文串的最少修改次数
def getModifyCnt(tt:str) -> int:
    if len(tt) < 1: return 0

    l = mx_cnt = len(tt)
    for d in divisors[l]:
        cnt = 0
        for off in range(d):
            t = tt[off::d]
            for i in range(len(t)//2):
                if t[i] != t[-i-1]: cnt += 1
        mx_cnt = min(mx_cnt, cnt)
    return mx_cnt

class Solution:
    def minimumChanges(self, s: str, k: int) -> int:
        n = len(s)
        @cache
        def dfs(i:int, j:int) -> int:
            if (j == 0 and i < n) or i == n-1:
                return inf
            if i == n and j == 0:
                return 0
            
            res = inf
            for nxt in range(i+2, n+1):
                res = min(res, getModifyCnt(s[i:nxt]) + dfs(nxt, j-1))
            return res
        return dfs(0, k)

if __name__ == "__main__":
    sol = Solution()
    s, k = "aaaaacabbb", 1
    print(getModifyCnt("aaaaacabbb"))
    print(sol.minimumChanges(s, k))

