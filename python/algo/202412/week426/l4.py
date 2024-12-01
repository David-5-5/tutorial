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

        # 第一次遍历 0 为根节点的各节点包含的所有子节点的距离为奇数、偶数的节点数
        # 第二次遍历，以各节点为根节点的包含所有字节的距离为奇数、偶数的节点数
        #   对于 u 和 fa, fa 为 u 根，当 u 为根节点时，fa 为 u 的子节点，其距离的变化公式为：
        #   1, 从 fa 减去以 u 为子节点的 距离分别为奇偶的数量，即
        #           new_fa_odd = ans[fa][0] - ans[u][1]
        #           new_fa_even = ans[fa][1] - ans[u][0]
        #   2, 节点 u 加上以 fa 为子节点后的距离为奇数、偶数的节点数
        #           ans[u][0] = ans[u][0] + new_fa_even
        #           ans[u][1] = ans[u][1] + new_fa_odd
        #  注，1、需要用临时变量，ans[u] 变化
        #     2、父子节点的解耦性互反
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
        # 换根 DP
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

    def maxTargetNodes2(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        # 基于 maxTargetNodes 抽象公共方法，简化代码
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

        def dfs(g:List[List[int]], u:int, fa:int, ans: List[List[int]]) :
            ans[u] = [0, 1]

            for v in g[u]:
                if v == fa:continue
                dfs(g, v, u, ans)
                ans[u][0] += ans[v][1]
                ans[u][1] += ans[v][0]
        
        dfs(g1, 0, -1, ans1)
        dfs(g2, 0, -1, ans2)

        mx_odd, _ = ans2[0]
        def reroot(g:List[List[int]], u:int, fa:int, need_mx:bool, ans: List[List[int]]):
            nonlocal mx_odd
            if fa != -1:
                fa_odd = ans[fa][0] - ans[u][1]
                fa_even = ans[fa][1] - ans[u][0]

                ans[u][0] = ans[u][0] + fa_even
                ans[u][1] = ans[u][1] + fa_odd
                if need_mx and ans[u][1] > mx_odd : mx_odd =  ans[u][1]

            for v in g[u]:
                if v == fa: continue
                reroot(g, v, u, need_mx, ans)

        reroot(g2, 0, -1, True, ans2)
        reroot(g1, 0, -1, False, ans1)
        return [even + mx_odd for _,even in ans1]

if __name__ == "__main__":
    sol = Solution()
    edges1, edges2 = [[0,1],[0,2],[2,3],[2,4]], [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
    edges1, edges2 = [[0,1],[0,2],[0,3],[0,4]], [[0,1],[1,2],[2,3]]

    print(sol.maxTargetNodes(edges1, edges2))
    print(sol.maxTargetNodes2(edges1, edges2))
