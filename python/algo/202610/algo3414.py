from bisect import bisect_left
from functools import cache
from math import inf
from typing import List


class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        # brute, TLE
        idx = [i for i, _  in sorted(enumerate(intervals), key=lambda p:p[1]) ]
        intervals.sort()
        
        n = len(intervals)
        @cache
        def dfs(i: int, j: int, k: int) -> int:
            if k == 0 or i == n: return 0
            l, r, w = intervals[i]

            if j>=0 and l <= intervals[j][1]:
                return dfs(i+1, j, k)

            return max(intervals[i][2] + dfs(i+1, i, k-1), dfs(i+1, j, k))
        
        mx = dfs(0, -1, 4)
        
        def trace(i: int, j: int, k: int, score: int) -> List[int]:
            if k == 0 or i == n: return []
            l, _, _ = intervals[i]

            if j>=0 and l <= intervals[j][1]:
                return trace(i+1, j, k, score)
            
            sel, n_sel = False, False
            if intervals[i][2] + dfs(i+1, i, k-1) == score:
                sel = True
                res1 = [idx[i]] + trace(i+1, i, k-1, score-intervals[i][2])
                res1.sort()
            if dfs(i+1, j, k) == score:
                n_sel = True
                res2 = trace(i+1, j, k, score)
                res2.sort()
            if sel and n_sel: return min(res1, res2)
            elif sel: return res1
            else: return res2
        
        return trace(0,-1,4, mx)
    
    def maximumWeight2(self, intervals: List[List[int]]) -> List[int]:
        idx = [i for i, _  in sorted(enumerate(intervals), key=lambda p:p[1][1])]

        # intervals.sort(key=lambda p: p[1])
        rs = [-1] + [intervals[i][1] for i in idx]
        n = len(intervals)
        
        dp = [[-inf] * (5) for _ in range(n+1)]
        last = [[-1] * (5) for _ in range(n+1)]
        dp[0][0] = 0
        for i in range(n):
            l, _, w = intervals[idx[i]]
            for k in range(5):
                dp[i+1][k] = dp[i][k]
            pi = bisect_left(rs, l) - 1 # 有哨兵
            for k in range(4):
                if dp[pi][k] == -inf: continue
                if w + dp[pi][k] >= dp[i+1][k+1]:
                    last[i+1][k+1] = pi
                    dp[i+1][k+1] = w + dp[pi][k]
        
        mx = max(dp[-1])

        @cache
        def trace(i:int, k: int, score: int) -> List[int]:
            if i == 0 or k == 0 or score == 0: return []
            _, _, w = intervals[idx[i-1]]
            res = []
            
            if dp[i][k] == score and last[i][k]>=0:
                res.append([idx[i-1]] + trace(last[i][k], k-1, score-w))
                
            if dp[i-1][k] == score:
                res.append(trace(i-1, k, score))

            for r in res: r.sort()
            return min(res)
        return min([trace(n, k, mx) for k in range(1, 5) if dp[n][k]==mx])
    
    def maximumWeight3(self, intervals: List[List[int]]) -> List[int]:
        a = [(r, l, weight, i) for i, (l, r, weight) in enumerate(intervals)]
        a.sort(key=lambda t: t[0])  # 按照右端点排序
        f = [[(0, []) for _ in range(5)] for _ in range(len(intervals) + 1)]
        for i, (_, l, weight, idx) in enumerate(a):
            k = bisect_left(a, (l,), hi=i)  # hi=i 表示二分上界为 i（默认为 n）
            for j in range(1, 5):
                # 为什么是 f[k] 不是 f[k+1]：上面算的是 >= l，-1 后得到 < l，但由于还要 +1，抵消了
                s2, id2 = f[k][j - 1]
                # 注意这里是减去 weight，这样取 min 后相当于计算的是最大和
                f[i + 1][j] = min(f[i][j], (s2 - weight, sorted(id2 + [idx])))

        return f[-1][4][1]

if __name__ == "__main__":
    print(Solution().maximumWeight4([[18,23,48],[1,19,11],[16,19,37],[3,18,25],[6,22,44],[18,21,27],[3,21,29],[6,20,29],[3,24,38],[3,5,44]]))