from typing import List

# 周赛 361
# 小结：1 建立图 -> dfs 求各节点 depth 以及计算 pa ->
#      2 根据题目要求，创建三维数组，记录各节点的查找根节点路径上的权重计数
#      3 lca 查找两个节点的最近公共祖先，求路径上的权重计数
class Solution:
    def minOperationsQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        # 参考题解
        g = [[] for _ in range(n)]
        m = n.bit_length()

        for u, v, w in edges:
            g[u].append((v, w))
            g[v].append((u, w))
        
        depth = [0] * n
        pa = [[-1] * m for _ in range(n)]
        # 适配题目代码
        cnt = [[[0] * 26 for _ in range(m) ] for _ in range(n)]

        def dfs(u: int, fa: int) -> None:
            pa[u][0] = fa
            for v, w in g[u]:
                if v != fa:
                    cnt[v][0][w] = 1
                    depth[v] = depth[u] + 1
                    dfs(v, u)
        dfs(0, -1)
        for i in range(m - 1):
            for u in range(n):
                if (p := pa[u][i]) != -1:
                    pa[u][i + 1] = pa[p][i]
                    for j, (c1, c2) in enumerate(zip(cnt[u][i], cnt[p][i])):
                        cnt[u][i+1][j] = c1 + c2
        
        ans = []
        for x, y in queries:
            # 树上倍增 lca 模板
            w_cnt = [0] * 26
            if depth[x] > depth[y]:
                x, y = y, x
            # 使 y 和 x 在同一深度
            k = depth[y] - depth[x]
            for i in range(k.bit_length()):
                if (k >> i) & 1:  # k 二进制从低到高第 i 位是 1
                    # 适配题目代码
                    for j, cy in enumerate(cnt[y][i]):
                        w_cnt[j] += cy
                    y = pa[y][i]
            if y != x:
                for i in range(len(pa[x]) - 1, -1, -1):
                    px, py = pa[x][i], pa[y][i]
                    if px != py:
                        # 适配题目代码
                        for j, (cx, cy) in enumerate(zip(cnt[x][i],cnt[y][i])):
                            w_cnt[j] += cx + cy
                        x, y = px, py  # 同时上跳 2**i 步
                # 适配题目代码
                for j, (c1, c2) in enumerate(zip(cnt[x][0], cnt[y][0])):
                    w_cnt[j] += c1 + c2                        
            
            ans.append(sum(w_cnt)-max(w_cnt))
        return ans

if __name__ == "__main__":
    sol = Solution()
    n, edges, queries = 7, [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], [[0,3],[3,6],[2,6],[0,6]]
    n, edges, queries = 8, [[1,2,6],[1,3,4],[2,4,6],[2,5,3],[3,6,6],[3,0,8],[7,0,2]],[[4,6],[0,4],[6,5],[7,4]]
    print(sol.minOperationsQueries(n, edges, queries))