from typing import List

# 周赛 365
class Solution:
    def countVisitedNodes(self, edges: List[int]) -> List[int]:
        n = len(edges)
        # g = [[] for _ in range(n)]
        deg = [0] * n

        for _, v in enumerate(edges):
            # g[u].append[v]
            deg[v] += 1

        # 查找第一个入度为零的节点
        zero_d_f = -1
        for i, d in enumerate(deg):
            if d == 0:
                zero_d_f = i
                break
        
        if zero_d_f == -1: return [n] * n # 所有节点都在环里

        # 从找到的入度为 0 的节点开始，查找环
        clocks = [0] * n
        c = 0
        def find_cycle(i:int) -> int:
            nonlocal c
            c += 1
            if clocks[i] != 0: return clocks[i]
            clocks[i] = c
            return find_cycle(edges[i])

        ans = [0] * n
        start = find_cycle(zero_d_f)
        v_cycle = set()
        for i, v in enumerate(clocks):
            if v >= start:
                v_cycle.add(i)
                ans[i] = c - start

        def dfs(i:int) -> int:
            if i in v_cycle: return ans[i]
            ans[i] = 1 + dfs(edges[i])
            return ans[i]
        
        for i, v in enumerate(ans):
            if v != 0:continue
            dfs(i)
        return ans

if __name__ == "__main__":
    sol = Solution()
    edges = [6,3,6,1,0,8,0,6,6]
    print(sol.countVisitedNodes(edges))
