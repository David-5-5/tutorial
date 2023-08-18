class Solution:
    def shortestPathLength(self, graph) -> int:
        '''
        One testcase fail. 
        Use dfs, traverse each vertex and small degree first
        '''
        n = len(graph)
        degree = [len(graph[i]) for i in range(n)]

        def next(u, left, visited):
            ret = -1
            degree = 12
            for v in graph[u]:
                if v not in visited and left[v] < degree:
                    ret = v
                    degree = left[v]
            return ret

        def dfs(u, left, visited, path):
            visited.append(u)
            path.append(u)
            v = next(u, left, visited) 
            while v != -1:
                left[u] -= 1
                left[v] -= 1
                dfs(v, left, visited, path)
                v = next(u, left, visited)
                # 
                if (v != -1):
                    inx = path.index(u)
                    l = len(path) - 1
                    if path[-1] in graph[path[inx]]:
                        left[path[-1]] -= 1
                        left[path[inx]] -= 1
                    for i in range(l, inx, -1):
                        if path[-1] not in graph[path[inx]]:
                            left[path[i]] -= 1
                            left[path[i-1]] -= 1
                        path.pop(-1)

        min_dg = min(degree)
        begins = []
        for i in range(n):
            if min_dg == degree[i]:
                begins.append(i)
        ans = float("inf")
        for u in begins:
            leftd = degree.copy()
            dfs(u, leftd, [], [])
            cnt = 0
            for i in range(n):
                cnt += degree[i] - leftd[i]
            ans = min(ans, cnt//2)

        return ans



    def shortestPathLength3(self, graph) -> int:
        '''
        The official solution
        Use bfs, (u, mask, distance), avoid repeat, to check (u,mask)
        '''
        n = len(graph)

        q = [(i, 1 << i, 0) for i in range(n)]
        seen = {(i, 1 << i) for i in range(n)}
        ans = 0
        
        while q:
            u, mask, dist = q.pop(0)
            if mask == (1 << n) - 1:
                ans = dist
                break
            # 搜索相邻的节点
            for v in graph[u]:
                # 将 mask 的第 v 位置为 1
                mask_v = mask | (1 << v)
                if (v, mask_v) not in seen:
                    q.append((v, mask_v, dist + 1))
                    seen.add((v, mask_v))
        
        return ans


if __name__ == "__main__":
    sol = Solution()
    graph = [[1,2,3],[0],[0],[0]]
    # graph = [[1],[0,2,6],[1,3],[2],[5],[4,6],[1,5,7],[6]]
    # graph = [[2,6],[2,3],[0,1],[1,4,5,6,8],[3,9,7],[3],[3,0],[4],[3],[4]]
    # graph = [[1,2,3,4],[0,2],[0,1],[0,5],[0,6],[3],[4]]
    # graph = [[6,9],[6,8],[6,7],[6,10],[8],[10],[0,1,2,3,8],[2,8,9],[1,4,6,7],[0,7,10],[3,5,9]]
    print(sol.shortestPathLength(graph))
    print(sol.shortestPathLength3(graph))
