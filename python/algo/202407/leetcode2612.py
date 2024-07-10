from bisect import bisect_left
from typing import List


class Solution:
    def minReverseOperations(self, n: int, p: int, banned: List[int], k: int) -> List[int]:
        ban = set(banned) | {p}

        rvs = [[],[]]
        for i in range(n):
            if i not in ban:
                rvs[i % 2].append(i)
        rvs[0].append(n)
        rvs[1].append(n)

        ans = [-1] * n

        q = [p]
        step = 0
        while q:
            nq = []
            for i in q:
                ans[i] = step
                mn = max(i-k+1, k-i-1)
                mx = min(i+k-1, 2*n-k-i-1)

                j = bisect_left(rvs[mn % 2], mn)
                while rvs[mn % 2][j] <= mx:
                    nq.append(rvs[mn % 2][j])
                    del rvs[mn % 2][j]

            step += 1
            q = nq
        return ans

if __name__ == "__main__":
    sol = Solution()
    n, p, banned, k = 4, 0,[1,2], 4
    print(sol.minReverseOperations(n, p, banned, k))