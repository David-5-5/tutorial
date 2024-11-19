from functools import cache
from math import inf


# 判断半回文 - 本题不用
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



class Solution:
    def minimumChanges(self, s: str, k: int) -> int:
        n = len(s)

        # 半回文串的最少修改次数，也需要cache
        @cache
        def getModifyCnt(begin:int, end:int) -> int:
            tt = s[begin:end]
            if len(tt) < 1: return 0

            l = mx_cnt = len(tt)
            for d in divisors[l]:
                cnt = 0
                for off in range(d):
                    t = tt[off::d]
                    for begin in range(len(t)//2):
                        if t[begin] != t[-begin-1]: cnt += 1
                mx_cnt = min(mx_cnt, cnt)
            return mx_cnt

        @cache
        def dfs(i:int, left:int) -> int:
            # if (left == 0 and i < n) or i == n-1:
            #     return inf
            # if i == n and left == 0:
            #     return 0
            
            # res = inf
            # for j in range(i+2, n+1):
            #     res = min(res, getModifyCnt(i,j) + dfs(j, left-1))
            # return res

            # 优化后的状态转移(避免无效的状态)，性能和上段代码相差 10 倍
            if left == 1: return getModifyCnt(i, n) # 仅一个子串
            res = inf
            for j in range(i+1, n-2*(left-1)):
                res = min(res, getModifyCnt(i,j+1) + dfs(j+1, left-1))
            return res
        return dfs(0, k)

    def minimumChanges2(self, s: str, k: int) -> int:
        # 反向递归，getModifyCnt 改为 modify array
        n = len(s)

        # 半回文串的最少修改次数，也需要cache
        @cache
        def getModifyCnt(begin:int, end:int) -> int:
            tt = s[begin:end+1]
            if len(tt) < 1: return 0

            l = mx_cnt = len(tt)
            for d in divisors[l]:
                cnt = 0
                for off in range(d):
                    t = tt[off::d]
                    for begin in range(len(t)//2):
                        if t[begin] != t[-begin-1]: cnt += 1
                mx_cnt = min(mx_cnt, cnt)
            return mx_cnt

        @cache
        def dfs(i:int, left:int) -> int:
            if left == 0: return getModifyCnt(0, i)
            res = inf
            for j in range(left*2, i):
                res = min(res, getModifyCnt(j,i) + dfs(j-1, left-1))
            return res
        return dfs(n-1, k-1)

if __name__ == "__main__":
    sol = Solution()
    s, k = "abcdef", 2
    print(sol.minimumChanges(s, k))
    print(sol.minimumChanges2(s, k))

