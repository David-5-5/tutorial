class Solution:
    def findRedundantDirectedConnection(self, edges):
        n = len(edges)

        def findCuttingEdge(n, edges):
            '''
            tarjan 塔尔杨
            强连通算法(无向图)，计算割点和割边
            '''
            bridge = []
            # 点的访问情况False: 未访问, True: 已访问 
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
                    if w not in graph[v]: graph[v].append(w)
                if w not in graph.keys():
                    graph[w] = [v]
                else:
                    if v not in graph[w]:graph[w].append(v)
                # 初始化边的访问情况
                setEdgeInSpan(v, w, False)

            def dfs(v: int, tim:int):
                # pre order
                dfn[v-1] = tim
                low[v-1] = tim
                vis[v-1] = True
                tim += 1
                if v in graph.keys():
                    for w in graph[v]:
                        if vis[w-1]:
                            if not span[(min(v,w), max(v,w))]:
                                # (v,w) is back edge
                                low[v-1] = min(low[v-1], dfn[w-1])
                        else:
                            setEdgeInSpan(v, w, True)
                            dfs(w, tim)
                            # post order, 
                            low[v-1] = min(low[w-1], low[v-1])
                            # cutting edge dfn[v] < low[w]
                            if dfn[v-1] < low[w-1]:
                                if not ([v,w]in edges and [w,v]in edges):
                                    bridge.append([v,w])
                                    bridge.append([w,v])
            for v, w in edges:
                addEdge(v, w)
            
            dfs(1, 0)
            return bridge



        # Find the cutting edges 
        # The edge should not in list of cutting edges
        bridges =  findCuttingEdge(n, edges)

        re_graph = {}
        for v, w in edges:
            if w not in re_graph.keys():
                re_graph[w] = [v]
            else:
                re_graph[w].append(v)
        
        # The edge link to vertex  which degree is 2
        # If exist, the edge should be included in
        edges_degree = []
        for w in re_graph.keys():
            if len(re_graph[w]) == 2:
                for v in re_graph[w]:
                    edges_degree.append([v,w])

        if edges_degree and bridges:
            if edges_degree[0] in bridges:
                return edges_degree[1]
            elif edges_degree[1] in bridges:
                return edges_degree[0] 
                    
        for i in range(n-1, -1, -1):
            if edges[i] not in bridges:                
                if not edges_degree:
                    return edges[i]
                elif edges[i] in edges_degree:
                    return edges[i]

if __name__ == "__main__":
    sol = Solution()
    edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
    # edges = [[1,3],[3,4],[1,5],[3,5],[2,3]]
    # edges = [[2,1],[3,1],[4,2],[1,4]]
    # edges = [[4,2],[1,5],[5,2],[5,3],[2,4]]
    edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
    edges = [[5,2],[5,1],[3,1],[3,4],[3,5]]
    print(sol.findRedundantDirectedConnection(edges))