from typing import List
from itertools import accumulate
class Solution:
    def totalStrength(self, strength: List[int]) -> int:
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