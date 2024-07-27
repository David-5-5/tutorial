from bisect import bisect_left
from typing import List

# Refer to 2022上半年周赛总结 https://leetcode.cn/circle/discuss/G0n5iY/
class Solution:
    def maximumScore(self, scores: List[int], edges: List[List[int]]) -> int:
        # 自行解答
        n = len(scores)

        g = [[] for _ in range(n)]
        for edge in edges:
            u, v = edge
            inx = bisect_left(g[u], (scores[v], v))
            g[u].insert(inx, (scores[v], v))
            inx = bisect_left(g[v], (scores[u], u))
            g[v].insert(inx, (scores[u], u))
        
        for i in range(n):
            g[i].sort(reverse=True)

        ans = -1
        for u, v in edges:
            if len(g[u]) == 1 or len(g[v]) == 1:
                continue
            if len(g[u]) == 2 and len(g[v]) == 2:
                x = g[u][0][1] if g[u][0][1] != v else g[u][1][1]
                y = g[v][0][1] if g[v][0][1] != u else g[v][1][1]
                if x == y: continue
                if scores[u]+scores[v]+scores[x]+scores[y] > ans:
                    ans = scores[u]+scores[v]+scores[x]+scores[y]
            
            mx1 = nx1 = mx2 = nx2 = p1 = p2 = 0
            for i in range(min(3, len(g[u]))):
                if g[u][i][1] == v:continue
                if mx1 == 0:
                    mx1, p1 = g[u][i]
                else:
                    nx1 = g[u][i][0]
            
            for i in range(min(3, len(g[v]))):
                if g[v][i][1] == u:continue
                if mx2 == 0:
                    mx2, p2 = g[v][i]
                else:
                    nx2 = g[v][i][0]
            
            val = scores[u] + scores[v] + (mx1 + mx2 if p1 != p2 else mx1 + max(nx1, nx2))
            if val > ans:
                ans = val
        
        return ans
    
if __name__ == "__main__":
    s = Solution()
    scores,edges = [5,2,9,8,4], [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
    scores,edges = [18,6,4,9,8,2], [[0,1],[0,2],[0,3],[0,4],[0,5],[1,2],[1,3],[1,4],[1,5],[2,3],[2,4],[2,5],[3,4],[3,5],[4,5]]
    print(s.maximumScore(scores, edges))    