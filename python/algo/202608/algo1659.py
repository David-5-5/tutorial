from functools import cache


class Solution:
    def getMaxGridHappiness(self, m: int, n: int, introvertsCount: int, extrovertsCount: int) -> int:
        
        @cache
        def dfs(i: int, inState: int, exState: int, inCnt: int, exCnt:int) -> int:
            if i == m * n: return 0
            if inCnt == 0 and exCnt == 0: return 0

            res = dfs(i+1, (inState<<1) & ((1<<n) - 1), (exState << 1) & ((1<<n) - 1), inCnt, exCnt)

            if inCnt:
                val = 120
                if inState >> (n-1) & 1:
                    val -= 60
                elif exState >> (n-1) & 1:
                    val -= 10
                if i % n:
                    if inState & 1:
                        val -= 60
                    elif exState & 1:
                        val -= 10
 
                res = max(res, val + dfs(i+1, ((inState << 1) | 1) & ((1<<n) - 1), (exState << 1) & ((1<<n) - 1), inCnt-1, exCnt))

            if exCnt:
                val = 40
                if inState >> (n-1) & 1:
                    val -= 10
                if exState >> (n-1) & 1:
                    val += 40
                if i % n:
                    if inState & 1:
                        val -= 10
                    if exState & 1:
                        val += 40

                res = max(res, val + dfs(i+1, (inState<<1) & ((1<<n) - 1), ((exState << 1) | 1) & ((1<<n) - 1), inCnt, exCnt-1))                

            return res
        
        ans = dfs(0, 0, 0, introvertsCount, extrovertsCount)
        return ans

