from tokenize import Triple
from typing import List


class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        # 自行解答 比赛时，时间不够。赛后提交通过
        n, m = len(edges1) + 1, len(edges2) + 1
        
        g1, g2 = [[] for _ in range(n)], [[] for _ in range(m)]
        for u, v in edges1:
            g1[u].append(v)
            g1[v].append(u)

        for u, v in edges2:
            g2[u].append(v)
            g2[v].append(u)

        ans1 = [[0,0] for _ in range(n)]
        ans2 = [[0,0] for _ in range(m)]

        def dfs1(u:int, fa:int) :
            ans1[u] = [0, 1]

            for v in g1[u]:
                if v == fa:continue
                dfs1(v, u)
                ans1[u][0] += ans1[v][1]
                ans1[u][1] += ans1[v][0]
        dfs1(0,-1)

        def dfs2(u:int, fa:int) :
            ans2[u] = [0, 1]

            for v in g2[u]:
                if v == fa:continue
                dfs2(v, u)
                ans2[u][0] += ans2[v][1]
                ans2[u][1] += ans2[v][0]
        
        dfs2(0, -1)

        mx_odd, _ = ans2[0]
        def reroot2(u:int, fa:int):
            nonlocal mx_odd
            if fa != -1:
                fa_odd = ans2[fa][0] - ans2[u][1]
                fa_even = ans2[fa][1] - ans2[u][0]

                ans2[u][0] = ans2[u][0] + fa_even
                ans2[u][1] = ans2[u][1] + fa_odd
                if ans2[u][1] > mx_odd : mx_odd =  ans2[u][1]

            for v in g2[u]:
                if v == fa: continue
                reroot2(v, u)

        reroot2(0, -1)
        
        def reroot1(u:int, fa:int):
            if fa != -1:
                fa_odd = ans1[fa][0] - ans1[u][1]
                fa_even = ans1[fa][1] - ans1[u][0]

                ans1[u][0] = ans1[u][0] + fa_even
                ans1[u][1] = ans1[u][1] + fa_odd 
            
            for v in g1[u]:
                if v == fa: continue
                reroot1(v, u)
        
        reroot1(0, -1)
        return [even + mx_odd for _,even in ans1]

if __name__ == "__main__":
    sol = Solution()
    edges1, edges2 = [[0,1],[0,2],[2,3],[2,4]], [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
    edges1, edges2 = [[0,1],[0,2],[0,3],[0,4]], [[0,1],[1,2],[2,3]]

    print(sol.maxTargetNodes(edges1, edges2))
