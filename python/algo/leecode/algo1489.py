class Solution:
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges) :
        critical, pseudo = [], []
        ne = len(edges)
        edgeI = {}
        for i in range(ne):
            edgeI[(min(edges[i][0],edges[i][1]), max(edges[i][0],edges[i][1]))] = i

        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]
        
        def union(x:int, y:int):
            root1 = find(x)
            root2 = find(y)
            if root1 == root2:
                cycle[root1] = True
                return
            if adt[root2] < adt[root1]:
                adt[root1] = root2
            else:
                if adt[root1] == adt[root2]:
                    adt[root1] -= 1
                adt[root2] = root1

        adt = [-1] * n
        cycle = [False] * n
        
        edges.sort(key=lambda p:p[2])
        candi = []
        weight = 0
        def appendCandiate(candi):
            for u, w in candi:
                union(u, w)
            
            for u, w in candi:
                if not cycle[find(u)]:
                    critical.append(edgeI[(u,w)])
                else:
                    pseudo.append(edgeI[(u,w)])
        i = 0
        while i < ne:
            u, w = edges[i][0], edges[i][1]
            if find(u) == find(w): 
                i += 1
                continue
            if not candi:
                candi = [(min(u,w), max(u,w))]
                weight = edges[i][2]
                i += 1
            elif weight == edges[i][2]:
                candi.append((min(u,w), max(u,w)))
                i += 1
            else:
                appendCandiate(candi)
                candi = []
        appendCandiate(candi)
        candi = []

        return [critical, pseudo]


    def findCriticalAndPseudoCriticalEdges2(self, n: int, edges) :
        visited = [False] * n
        critical, pseudo = [], []
        
        # The key is fromi/toi, the value is list, element of (weigthi, toi/fromi, i)
        # And list sorted by weigth
        graph = {}
        from bisect import bisect_right
        
        def dfs(vertex: int):
            while graph[vertex] and visited[graph[vertex][0][1]]:
                graph[vertex].pop(0)
            
            if graph[vertex]:
                weight, toi, i = graph[vertex].pop(0)
                isCritical = True
                inx = 0
                while not isCritical and inx < graph[vertex] and weight == graph[vertex][inx][0]:
                    if not visited[graph[vertex][i][1]]:
                        isCritical = False
                    inx += 1
                if isCritical:
                    critical.append(i)
                else:
                    pseudo.append(i)
                dfs(toi)

        for i in range(len(edges)):
            if edges[i][0] in graph.keys():
                inx = bisect_right(graph[edges[i][0]], (edges[i][2], edges[i][1], i))
                graph[edges[i][0]].insert(inx, (edges[i][2], edges[i][1], i))
            else:
                graph[edges[i][0]] = [(edges[i][2], edges[i][1], i)]

            if edges[i][1] in graph.keys():
                inx = bisect_right(graph[edges[i][1]], (edges[i][2], edges[i][0], i))
                graph[edges[i][1]].insert(inx, (edges[i][2], edges[i][0], i))
            else:
                graph[edges[i][1]] = [(edges[i][2], edges[i][0], i)]

        for i in range(n):
            if visited[i]:
                continue
            else:
                visited[i] = True
                dfs(i)

        return [critical, pseudo]

    def findCriticalAndPseudoCriticalEdges3(self, n: int, edges) :
        critical, pseudo = [], []
        ne = len(edges)
        edgeI = {}
        for i in range(ne):
            edgeI[(min(edges[i][0],edges[i][1]), max(edges[i][0],edges[i][1]))] = i
        
        def findCuttingEdge(n, edges):
            '''
            tarjan 塔尔杨
            强连通算法(无向图)，计算割点和割边
            '''
            bridge = []
            # 点的访问情况0: 未访问, 1: 正在访问, 2: 已访问 
            vis = [False] * n
            # 代表该节点被访问的次序。对于数组 dfn, 使用一个全局变量tim进行赋值, 
            # 每访问到一个新节点 X ( 即vis[X]==0 ), 则 dfn[X]=tim++
            dfn = [0] * n
            # 代表 X节点与X节点的子树 能回溯到的 最小的dfn值
            low = [0] * n
            
            # key (v,w), v<w; value: True/False. True表示边在生成树中, False, 表明边是back edge
            span = {}
            def setEdgeInSpan(v:int , w: int, visited:bool):
                if v < w:
                    span[(v, w)] = visited
                else:
                    span[(w, v)] = visited
            
            # key v, value: [w, u]
            graph = {}
            def addEdge(v: int, w: int):
                if v not in graph.keys():
                    graph[v] = [w]
                else:
                    graph[v].append(w)
                if w not in graph.keys():
                    graph[w] = [v]
                else:
                    graph[w].append(v)
                # 初始化边的访问情况
                setEdgeInSpan(v, w, False)

            def dfs(v: int, tim:int):
                # pre order
                dfn[v] = tim
                low[v] = tim
                vis[v] = True
                tim += 1
                if v in graph.keys():
                    for w in graph[v]:
                        if vis[w]:
                            if not span[(min(v,w), max(v,w))]:
                                # (v,w) is back edge
                                low[v] = min(low[v], dfn[w])
                        else:
                            setEdgeInSpan(v, w, True)
                            dfs(w, tim)
                            # post order, 
                            low[v] = min(low[w], low[v])
                            # cutting edge dfn[v] < low[w]
                            if dfn[v] < low[w]:
                                bridge.append((v,w))
            for v, w, _ in edges:
                addEdge(v, w)
            
            dfs(0, 0)
            return bridge

        mst = []
        for edge in findCuttingEdge(n, edges):
            critical.append(edgeI[edge])
            mst.append(edge)

        edges.sort(key=lambda p:p[2])

        # 0 : abandn, 1: pseudo, 2: critical
        def appendToMst(n, candi) -> int:
            org = len(mst)
            def addEdge(graph, span, v: int, w: int):
                if v not in graph.keys():
                    graph[v] = [w]
                else:
                    graph[v].append(w)
                if w not in graph.keys():
                    graph[w] = [v]
                else:
                    graph[w].append(v)
                # 初始化边的访问情况
                span[(min(v, w), max(v,w))] = False
                return graph, span
            vis = [False] * n
            selected = [True] * len(candi)
            def dfs(graph, span, v, i):
                if v in graph.keys():
                    vis[v] = True
                    for w in graph[v]:
                        if vis[w]:
                            if not span[(min(v,w), max(v,w))]:
                                selected[i] = False
                        else:
                            span[(min(v, w), max(v,w))] = True
                            dfs(graph, span, w, i)
            for i in range(len(candi)):
                graph = {}
                span = {}
                vis = [False] * n
                for v, w in mst:
                    addEdge(graph, span, v, w)
                addEdge(graph, span, candi[i][0], candi[i][1])
                dfs(graph, span, candi[i][0], i)
                if selected[i]:
                    mst.append(candi[i])
            if org == len(mst):
                return 0
            elif org + len(candi) == len(mst):
                return 2
            else: return 1
            
        candi = []
        weight = 0
        def appendCandiate(candi):
            state = appendToMst(n, candi)
            if state == 2:
                for edge in candi:
                    critical.append(edgeI[edge])
            elif state == 1:
                for edge in candi:
                    pseudo.append(edgeI[edge])
        i = 0
        while i < ne:
            u, w = edges[i][0], edges[i][1]
            if edgeI[(min(u,w), max(u,w))] in critical:
                i += 1
                continue
            if not candi:
                candi = [(min(u,w), max(u,w))]
                weight = edges[i][2]
                i += 1
            elif weight == edges[i][2]:
                candi.append((min(u,w), max(u,w)))
                i += 1
            else:
                appendCandiate(candi)
                candi = []
        appendCandiate(candi)
        candi = []

        return [critical, pseudo]


if __name__ == "__main__":
    sol = Solution()
    # edges, n = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]], 5
    # edges, n = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]], 4
    # edges, n = [[0,1,1],[0,2,1],[1,2,1],[2,3,1],[3,4,1],[3,5,1],[4,5,1]], 6
    # edges, n = [[0,1,1],[0,2,2],[1,2,3]], 3
    # edges, n = [[0,1,2],[0,2,5],[2,3,5],[1,4,4],[2,5,5],[4,5,2]], 6
    edges, n = [[0,1,13],[0,2,6],[2,3,13],[3,4,4],[0,5,11],[4,6,14],[4,7,8],[2,8,6],[4,9,6],[7,10,4],[5,11,3],[6,12,7],[12,13,9],[7,13,2],[5,13,10],[0,6,4],[2,7,3],[0,7,8],[1,12,9],[10,12,11],[1,2,7],[1,3,10],[3,10,6],[6,10,4],[4,8,5],[1,13,4],[11,13,8],[2,12,10],[5,8,1],[3,7,6],[7,12,12],[1,7,9],[5,9,1],[2,13,10],[10,11,4],[3,5,10],[6,11,14],[5,12,3],[0,8,13],[8,9,1],[3,6,8],[0,3,4],[2,9,6],[0,11,4],[2,5,14],[4,11,2],[7,11,11],[1,11,6],[2,10,12],[0,13,4],[3,9,9],[4,12,3],[6,7,10],[6,8,13],[9,11,3],[1,6,2],[2,4,12],[0,10,3],[3,12,1],[3,8,12],[1,8,6],[8,13,2],[10,13,12],[9,13,11],[2,11,14],[5,10,9],[5,6,10],[2,6,9],[4,10,7],[3,13,10],[4,13,3],[3,11,9],[7,9,14],[6,9,5],[1,5,12],[4,5,3],[11,12,3],[0,4,8],[5,7,8],[9,12,13],[8,12,12],[1,10,6],[1,9,9],[7,8,9],[9,10,13],[8,11,3],[6,13,7],[0,12,10],[1,4,8],[8,10,2]], 14
    print(sol.findCriticalAndPseudoCriticalEdges3(n, edges))