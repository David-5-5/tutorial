class Solution:
    def shortestPathLength(self, graph) -> int:
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


    def shortestPathLength2(self, graph) -> int:
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
        
        def dfs(u, left, visited, bt, path):
            visited.append(u)
            path.append(u)
            v = next(u, left, visited) 
            while v != -1:
                left[u] -= 1
                left[v] -= 1
                dfs(v, left, visited, bt, path)
                if bt[v]:
                    mid = False
                    for i in range(bt[v][-1]):
                        if path[-1-i] in graph[u]:
                            bt[u].append(1 + i)
                            mid = True
                            break
                    if not mid: bt[u].append(bt[v][-1] + 1)
                else:
                    bt[u].append(1)
                v = next(u, left, visited) 
        min_dg = min(degree)
        begins = []
        for i in range(n):
            if min_dg == degree[i]:
                begins.append(i)
        ans = float("inf")
        for u in begins:
            bt = [[] for _ in range(n)]
            leftd = degree.copy()
            dfs(u, leftd, [], bt, [])
            cnt = 0
            for i in range(n):
                bt[i].sort()
                for j in range(len(bt[i])-1):
                    cnt += bt[i][j]
            ans = min(ans, cnt + n -1)

        return ans

if __name__ == "__main__":
    sol = Solution()
    graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
    graph = [[2,6],[2,3],[0,1],[1,4,5,6,8],[3,9,7],[3],[3,0],[4],[3],[4]]
    graph = [[1,2,3,4],[0,2],[0,1],[0,5],[0,6],[3],[4]]
    graph = [[6,9],[6,8],[6,7],[6,10],[8],[10],[0,1,2,3,8],[2,8,9],[1,4,6,7],[0,7,10],[3,5,9]]
    print(sol.shortestPathLength(graph))
    print(sol.shortestPathLength2(graph))
