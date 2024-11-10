from collections import defaultdict
from typing import List


class Solution:
    def sumOfGoodSubsequences(self, nums: List[int]) -> int:
        MOD = 10 ** 9 + 7
        s = defaultdict(int)
        cnt = defaultdict(int)
        ans = 0

        for v in nums:
            c = 1
            ss = 0
            if v-1 in s.keys():
                ss += s[v-1]
                c += cnt[v-1]
            if v+1 in s.keys():
                ss += s[v+1]
                c += cnt[v+1]
            g = ss + c * v
            ans = (ans + g) % MOD
            cnt[v] += c
            s[v] += g

        return ans % MOD


if __name__ == "__main__":
    sol = Solution()
    nums = [8,4,5]
    print(sol.sumOfGoodSubsequences(nums))