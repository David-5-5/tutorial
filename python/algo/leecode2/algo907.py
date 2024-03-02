from typing import List
from math import factorial
class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        MOD = 10 ** 9 + 7
        n = len(arr)
        left, right, st = [-1] * n, [n]* n, []
        for i, v in enumerate(arr):
            while st and arr[st[-1]] >= v: right[st.pop()] = i
            if st: left[i] = st[-1]
            st.append(i)
        ans = 0
        for i, v in enumerate(arr):
            p, q = right[i] - i, i-left[i]
            ans =  (ans + v * p * q) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    arr = [11,81,94,43,3]
    print(sol.sumSubarrayMins(arr))