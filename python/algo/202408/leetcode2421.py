from typing import List

# 周赛 312
class Solution:
    def numberOfGoodPaths(self, vals: List[int], edges: List[List[int]]) -> int:
        n = len(vals)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        fa = list(range(n))
        def find(x:int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]

        ans = n
        size = [1] * n # 表示 x 所属连通块中值等于 vals[x] 的数量
        for val, u in sorted(zip(vals, range(n))):
            fu = find(u) # 取 u 所在连通块的代表元
            for v in g[u]:
                fv = find(v)
                # 情况 1) fv 和 fu 已经在一个连通块中
                # 情况 2) vals[fv] 大于当前处理的值，以后处理
                if fv == fu or vals[fv] > val:continue
                if vals[fv] == val:
                    ans += size[fv] * size[fu] # 乘法原理，两个连通块中等于val的节点数量
                    size[fu] += size[fv] # 将等于 val 的节点数量合并到代表元
                fa[fv] = fu # 合并连通块，fu 为代表元
        return ans

    def numberOfGoodPaths2(self, vals: List[int], edges: List[List[int]]) -> int:
        # 合并 size 和 fa 数组
        n = len(vals)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        fa = [-1] * n #代表元存储连通块中节点值等于 vals[x] 的数量
        def find(x:int) -> int:
            if fa[x] < 0:
                return x
            else:
                fa[x] = find(fa[x])
                return fa[x]
        
        # 合并两个连通块的单位元, x 为新连通块的单位元
        def union(x:int, y:int):
            if vals[x] == vals[y]:
                fa[x] += fa[y]
            fa[y] = x

        ans = n
        for val, u in sorted(zip(vals, range(n))):
            fu = find(u) # 取 u 所在连通块的代表元
            for v in g[u]:
                fv = find(v)
                # 情况 1) fv 和 fu 已经在一个连通块中
                # 情况 2) vals[fv] 大于当前处理的值，以后处理
                if fv == fu or vals[fv] > val:continue
                if vals[fv] == val:
                    ans += fa[fv] * fa[fu] # 乘法原理，两个连通块中等于val的节点数量
                union(fu, fv) # 合并连通块，fu 为代表元
        return ans


if __name__ == "__main__":
    sol = Solution()
    vals, edges = [1,3,2,1,3], [[0,1],[0,2],[2,3],[2,4]]
    vals, edges = [1,1,2,2,3], [[0,1],[1,2],[2,3],[2,4]]
    print(sol.numberOfGoodPaths(vals, edges))
    print(sol.numberOfGoodPaths2(vals, edges))


