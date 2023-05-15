class Solution:
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges) :
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

        for edge in findCuttingEdge(n, edges):
            critical.append(edgeI[edge])

        visited = [False] * n
        edges.sort(key=lambda p:p[2])
        def isCicle(candi) -> bool:
            isCicle = False
            for u, w in candi:
                if visited[u] and visited[w]:
                    isCicle = True
                else:
                    visited[u], visited[w] = True, True
            return isCicle
        candi = []
        weight = 0
        for i in range(ne):
            u, w = edges[i][0], edges[i][1]
            if visited[u] and visited[w]:
                continue
            if edgeI[(min(u,w), max(u,w))] in critical:
                continue
            if not candi:
                candi = [(min(u,w), max(u,w))]
                weight = edges[i][2]
            elif weight == edges[i][2]:
                candi.append((min(u,w), max(u,w)))
            else:
                if len(candi) == 1:
                    critical.append(edgeI[candi[0]])
                elif not isCicle(candi):
                    for edge in candi:
                        critical.append(edgeI[edge])
                else:
                    for edge in candi:
                        pseudo.append(edgeI[edge])

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


if __name__ == "__main__":
    sol = Solution()
    edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
    print(sol.findCriticalAndPseudoCriticalEdges(5, edges))