class Solution:
    def criticalConnections(self, n: int, connections) :
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
                            bridge.append([v,w])


        for v, w in connections:
            addEdge(v, w)
        
        dfs(0, 0)
        return bridge

if __name__ == "__main__":
    sol = Solution()
    # edges = [[0,1],[1,2],[2,0],[1,3]]
    # edges = [[0,1,3],[0,2],[1,2],[2,3],[3,4],[3,5],[4,5]]
    edges = [[0,1]]
    print(sol.criticalConnections(2, edges))