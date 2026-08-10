from collections import defaultdict
from typing import List


class Solution:
    def smallestUniqueSubarray(self, nums: List[int]) -> int:
        # 自行解答 Rabin Karp + 二分
        n, base, mod = len(nums), 113, 10 ** 9 + 7

        # length 下 的单 字符串哈希
        def check(lenght: int) -> bool:
            if lenght == 0: return True
            hash, blen = 0, pow(base, lenght-1, mod)
            freqs = defaultdict(int)
            
            for i in range(lenght):
                hash = (hash * base + nums[i]) % mod
            
            freqs[hash] += 1
            for i in range(lenght, n):
                hash = ((hash - nums[i-lenght]*blen) * base  + nums[i]) % mod
                freqs[hash] += 1

            return any([x == 1 for x in freqs.values()])

        l, r = 0, n + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid): r = mid
            else: l = mid

        return r