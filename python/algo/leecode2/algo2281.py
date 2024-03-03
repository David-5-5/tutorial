from typing import List
from itertools import accumulate
class Solution:
    def totalStrength(self, strength: List[int]) -> int:
        # 各元素的区间参见 algo907
        # 各元素的贡献值计算
        # .... 8 9 ... 5 ... 7 6 ....
        #      l       i       r
        # [8, 9 ...5]          s[i+1] - s[l]
        #       ...
        # [8, 9 ...5 ... 7]    s[r] - s[l]
        # [8, 9 ...5 ... 7 6]  s[r+1] - s[l]
        # [9 ...5]             s[i+1] - s[l+1]
        #       ...
        # [9 ...5 ... 7]       s[l] - s[l+1]
        # [9 ...5 ... 7 6]     s[l+1] - s[l+1]
        #       ...
        # [5]                  s[i+1] - s[i]
        #       ...
        # [5 ... 7]            s[l] - s[i]
        # [5 ... 7 6]          s[l+1] - s[i]
        # 上式相加得到：
        # (l - i + 1) * sum(s[i+1], ..., s[r+1]) - (r - i + 1)(sum(s[l], .... sum[i]))
        # 注: s 为 strengthd 的前缀和，ss 为 s的前缀和，上式转化为：
        # (l - i + 1) * （ss[r+2]-ss[i+1]) - (r - i + 1)(ss[i+1]-ss[l]))
        # 注: s 增加 0 了作为起始元素， ss 同样增加 0 作为起始元素
        #     strength[i..j]之间的前缀和为 s[j+1] - s[i]
        #     s[i.. j+1] 之间的前缀和为 ss[j+2] - ss[i]
        MOD = 10 ** 9 + 7
        n = len(strength)
        left, right, st = [-1] * n, [n]* n, []
        for i, v in enumerate(strength):
            while st and strength[st[-1]] >= v: right[st.pop()] = i
            if st: left[i] = st[-1]
            st.append(i)        

        # 前缀和的前缀和 strength
        ss = list(accumulate(accumulate(strength, initial=0), initial=0))
        
        ans = 0
        for i, v in enumerate(strength):
            l, r = left[i] + 1, right[i] - 1
            ans = (ans + v * ((i-l+1)*(ss[r+2]-ss[i+1]) - (r-i+1)*(ss[i+1]-ss[l]))) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    strength = [1,3,1,2]
    print(sol.totalStrength(strength))