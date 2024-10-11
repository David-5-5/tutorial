from collections import defaultdict
from functools import cache
from math import inf

# 双周赛 130
class Solution:
    def minimumSubstringsInPartition(self, s: str) -> int:
        # 自行解答
        n = len(s)

        @cache
        def dfs(i:int) -> int:
            if i == n: return 0

            cnt = defaultdict(int)
            res = inf
            for j in range(i, n):
                cnt[s[j]] += 1
                val = cnt[s[j]]
                if all(v == val for v in cnt.values()):
                    res = min(res, 1+dfs(j+1))
            return res
        return dfs(0)

    def minimumSubstringsInPartition(self, s: str) -> int:
        # 参考题解，优化平衡字符串判断
        n = len(s)

        @cache
        def dfs(i:int) -> int:
            if i == n: return 0

            cnt = defaultdict(int)
            res, max_cnt = inf, 0
            for j in range(i, n):
                cnt[s[j]] += 1
                if cnt[s[j]] > max_cnt: max_cnt = cnt[s[j]]
                if max_cnt * len(cnt) == j - i + 1:
                    res = min(res, 1+dfs(j+1))
            return res
        return dfs(0)
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumSubstringsInPartition("fabccddg"))