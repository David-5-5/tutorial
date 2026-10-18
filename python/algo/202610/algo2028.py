from typing import List


class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        r_sum, m = sum(rolls), len(rolls)

        r_left = mean * (n+m) - r_sum
        if r_left < n or r_left > n * 6: return []

        ans = []
        while r_left:
            ans.append(r_left // n)
            n -= 1
            r_left -= ans[-1]
        return ans

    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        r_sum, m = sum(rolls), len(rolls)

        r_left = mean * (n+m) - r_sum
        if r_left < n or r_left > n * 6: return []

        cnt = r_left % n
        return [r_left//n] * (n-cnt) + [r_left//n+1] * cnt