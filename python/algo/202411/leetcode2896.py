from functools import cache
from math import inf

# 周赛 366
class Solution:
    def minOperations(self, s1: str, s2: str, x: int) -> int:
        # 参考题解 时间复杂度 O(n^2)
        if s1.count('1') % 2 != s2.count('1') % 2: return -1

        # 参数 j 表示使用方法一反转后，得到免费字符反转的次数
        # pre_rev 前一个字符表示使用方法二反转，当前 s[i] 已经变化
        @cache
        def dfs(i:int, j:int, pre_rev:bool):
            if i == len(s1): return 0
            # 字符相同，不需要反转
            # if (s1[i] == s2[i] and not pre_rev) or (s1[i] != s2[i] and pre_rev):
            if (s1[i]==s2[i]) == (not pre_rev): # 条件优化
                return dfs(i+1, j, False)
            
            res = inf
            # 字符不相同，需要反转
            if j > 0:res = min(res, dfs(i+1, j-1, False)) # 使用方法二 免费反转一次
            res = min(res, x + dfs(i+1, j+1, False)) # 使用方法二 反转一次
            res = min(res, 1 + dfs(i+1, j, True)) # 使用方法一 反转一次
            
            return res

        return dfs(0, 0, False)

    def minOperations2(self, s1: str, s2: str, x: int) -> int:
        # 参考题解 时间复杂度 O(n)
        # 类似 打家劫舍
        if s1.count('1') % 2 != s2.count('1') % 2: return -1
        
        p = [i for i, (c1, c2) in enumerate(zip(s1,s2)) if c1 != c2]

        @cache
        # def dfs(i:int) -> int:
        #     if i < 0: return 0
        #     if i == 0: return x / 2

        #     return min(dfs(i-1)+x/2, dfs(i-2)+p[i]-p[i-1])

        # return int(dfs(len(p)-1))
        
        def dfs(i:int) -> int:
            if i < 0: return 0
            if i == 0: return x

            return min(dfs(i-1)+x, dfs(i-2)+2*(p[i]-p[i-1]))

        return dfs(len(p)-1) // 2


if __name__ == "__main__":
    sol = Solution()
    print(sol.minOperations("00101101100010", "00001010001111", 30))
    print(sol.minOperations2("00101101100010", "00001010001111", 30))