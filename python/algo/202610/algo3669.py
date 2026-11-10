from math import inf, sqrt
from typing import List

class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        mn_diff, ans = inf, []
        splits = [0] * k
        def dfs(N: int, K: int):
            nonlocal ans, mn_diff
            # if K and max(splits[0:K])-min(splits[0:K]) >= mn_diff: return
            
            if K == k-1:
                splits[K] = N
                if mn_diff > max(splits)-min(splits):
                    ans = splits.copy()
                    mn_diff = max(splits)-min(splits)
                return
            limit = int(sqrt(N)) + 1
            for f in range(1,limit):
                if N % f: continue
                splits[K] = f
                dfs(N//f, K+1)

        dfs(n, 0)
        return ans


if __name__ == "__main__":
    print(Solution().minDifference(18, 5))