class Solution:
    '''
    计算图的强连通性, 有tarjan 塔尔杨及Kosaraju科萨拉朱两种算法。割点和割边(桥)
    输入参数
       n: 点的数量, 点的ID为0, 1, .., n-1
       edges:边的信息，每条表的信息为[from, to], from和to为点的ID
    '''
    def tarjan(self, n, edges):
        '''
        tarjan 塔尔杨
        强连通算法(无向图)，计算割点和割边
        '''
        cutpiont = []
        bridge = []
        # 点的访问情况
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
            # rule 1 for low
            low[v] = tim
            vis[v] = True
            tim += 1
            if v in graph.keys():
                for w in graph[v]:
                    if vis[w]:
                        if not span[(min(v,w), max(v,w))]:
                            # rule 2 of low , when (v,w) is back edge
                            low[v] = min(low[v], dfn[w])
                    else:
                        setEdgeInSpan(v, w, True)
                        dfs(w, tim)
                        # post order, 
                        low[v] = min(low[w], low[v])
                        # rule 3 of low, cutting edge dfn[v] < low[w]
                        # v is parent node to w, in minimize spanning tree.
                        if dfn[v] < low[w]:
                            bridge.append((v,w))
                        # if v == 0, it is root node. The cut piont of root is
                        # wether or not it has multiple children.
                        if v != 0 and low[w] >= dfn[v] and v not in cutpiont:
                            cutpiont.append(v)


        for v, w in edges:
            addEdge(v, w)
        
        dfs(0, 0)
        # Judge if root is cut piont
        count = 0
        for w in graph[0]:
            if span[(0, w)]: count += 1
        if count > 1:
            cutpiont.append(0)
        
        return [cutpiont, bridge]

if __name__ == "__main__":
    sol = Solution()
    # edges, n = [[0,1],[1,2],[2,0],[1,3]], 4
    # edges, n = [[0,1],[0,2],[1,2],[2,3],[3,4],[3,5],[4,5]], 6
    # edges, n = [[0,1]], 2
    # edges, n = [[0,1],[3,2],[2,0],[0,3]], 4
    edges, n = [[0,1],[0,2],[1,2],[0,3],[4,3],[4,5],[0,5],[6,5]], 7
    print(sol.tarjan(n, edges))