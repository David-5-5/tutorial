from math import perm

# 周赛 309
class Solution:
    def numberOfWays(self, startPos: int, endPos: int, k: int) -> int:
        MOD = 10**9 + 7
        length = abs(endPos - startPos)
        if k < length or (k - length) % 2 == 1: return 0

        l = (k - length) // 2 + length
        r = (k - length) // 2
        return (perm(l+r)//perm(l)//perm(r)) % MOD

    
if __name__ == "__main__":
    sol = Solution()
    startPos, endPos, k = 1, 2, 3
    print(sol.numberOfWays(startPos, endPos, k))