class Solution:
    def reachableNodes(self, edges, maxMoves: int, n: int) -> int:

        # key v, value: [w, u]
        graph = {}
        # key edge(v,w) and v < w
        # value (cnt, left_cnt, rigth_cnt)
        # When left_cnt + right_cnt < n, the visted count of edge is 
        #       left_cnt + right_cnt
        # and when left_cnt + right_cnt >= n, the visted count of edge is 
        #       n
        vis_edge = {}

        vis_vec = [-1 for _ in range(n)]
        
        def initial(edge):
            if edge[0] not in graph.keys():
                graph[edge[0]] = [edge[1]]
            else:
                graph[edge[0]].append(edge[1])
            if edge[1] not in graph.keys():
                graph[edge[1]] = [edge[0]]
            else:
                graph[edge[1]].append(edge[0])
            
            vis_edge[(edge[0],edge[1])] = [edge[2], 0, 0]
        
        def dfs(v, reminder):
            vis_vec[v] = reminder
            if v not in graph.keys(): return
            for w in graph[v]:
                vis_edge[(min(v,w),max(v,w))][1 if v < w else 2] = min(reminder, vis_edge[(min(v,w),max(v,w))][0])
                if reminder-vis_edge[(min(v,w),max(v,w))][0]-1 > vis_vec[w]:
                    dfs(w, reminder-vis_edge[(min(v,w),max(v,w))][0]-1)
        
        for edge in edges:
            initial(edge)
        
        dfs(0, maxMoves)

        ans = 0
        for cnt, left_cnt, right_cnt in vis_edge.values():
            if  left_cnt + right_cnt < cnt:
                ans += left_cnt + right_cnt
            else:
                ans += cnt

        for vis in vis_vec:
            if vis>-1: ans += 1
        return ans

    def reachableNodes2(self, edges, maxMoves: int, n: int) -> int:
        ans = 0
        # key v, value: [w, u]
        graph = {}
        # key edge(v,w) and v < w
        # value (cnt, left_cnt, rigth_cnt)
        # When left_cnt + right_cnt < n, the visted count of edge is 
        #       left_cnt + right_cnt
        # and when left_cnt + right_cnt >= n, the visted count of edge is 
        #       n
        vis_edge = {}

        vis_vec = [-1 for _ in range(n)]
        
        def initial(edge):
            if edge[0] not in graph.keys():
                graph[edge[0]] = [[edge[1], edge[2]]]
            else:
                graph[edge[0]].append([edge[1], edge[2]])
            if edge[1] not in graph.keys():
                graph[edge[1]] = [[edge[0], edge[2]]]
            else:
                graph[edge[1]].append([edge[0], edge[2]])
            
            vis_edge[(edge[0],edge[1])] = [edge[2], 0, 0]
        
        def addTodo(v, todo, reminder):
            if (reminder > vis_vec[v]):
                vis_vec[v] = reminder
                if v in graph.keys():
                    for w, _ in graph[v]:
                        todo.append((w, v, reminder))

        def bfs(begin, reminder):
            todo = []
            addTodo(begin, todo, reminder)
            while todo:
                w, v, rem = todo.pop(0)
                vis_edge[(min(v,w),max(v,w))][1 if v < w else 2] = min(rem, vis_edge[(min(v,w),max(v,w))][0])
                addTodo(w, todo, rem - vis_edge[(min(v,w),max(v,w))][0]-1)

        for edge in edges:
            initial(edge)

        for v in range(n):
            if v in graph.keys():
                graph[v].sort(key=lambda s:s[1])
        
        bfs(0, maxMoves)

        
        for cnt, left_cnt, right_cnt in vis_edge.values():
            if  left_cnt + right_cnt < cnt:
                ans += left_cnt + right_cnt
            else:
                ans += cnt

        for vis in vis_vec:
            if vis>-1: ans += 1
        return ans

    def reachableNodes3(self, edges, maxMoves: int, n: int) -> int:
        ans = 0
        # key v, value: [w, u]
        graph = {}
        # key edge(v,w) and v < w
        # value (cnt, left_cnt, rigth_cnt)
        # When left_cnt + right_cnt < n, the visted count of edge is 
        #       left_cnt + right_cnt
        # and when left_cnt + right_cnt >= n, the visted count of edge is 
        #       n
        vis_edge = {}

        vis_vec = [-1 for _ in range(n)]
        
        def initial(edge):
            if edge[0] not in graph.keys():
                graph[edge[0]] = [[edge[1], edge[2]]]
            else:
                graph[edge[0]].append([edge[1], edge[2]])
            if edge[1] not in graph.keys():
                graph[edge[1]] = [[edge[0], edge[2]]]
            else:
                graph[edge[1]].append([edge[0], edge[2]])
            
            vis_edge[(edge[0],edge[1])] = [edge[2], 0, 0]
        
        
        todoEdges = []
        todoVec = []
        from bisect import bisect_right

        def addTodoEdges(v, reminder):
            if (reminder > vis_vec[v]):
                vis_vec[v] = reminder
                if v in graph.keys():
                    for w, _ in graph[v]:
                        todoEdges.append((w, v, reminder))

        def addTodoVec(v, reminder):
            if v in graph.keys():
                for w, cnt in graph[v]:
                    if reminder-cnt > vis_vec[w]:
                        inx = bisect_right(todoVec, (reminder-cnt-1, w))
                        todoVec.insert(inx, (reminder-cnt-1, w))

        def bfs():

            while todoEdges or todoVec:
                while not todoEdges and todoVec:
                    rem, cur = todoVec.pop(-1)
                    addTodoEdges(cur, rem)
                    addTodoVec(cur, rem)

                while todoEdges:
                    w, v, rem = todoEdges.pop(0)
                    vis_edge[(min(v,w),max(v,w))][1 if v < w else 2] = min(rem, vis_edge[(min(v,w),max(v,w))][0])


        for edge in edges:
            initial(edge)
        
        todoVec.append((maxMoves, 0))
        bfs()

        
        for cnt, left_cnt, right_cnt in vis_edge.values():
            if  left_cnt + right_cnt < cnt:
                ans += left_cnt + right_cnt
            else:
                ans += cnt

        for vis in vis_vec:
            if vis>-1: ans += 1
        return ans


if __name__ == "__main__":
    sol = Solution()
    edges, maxMoves, n = [[0,1,10],[0,2,1],[1,2,2]], 6, 3
    edges, maxMoves, n = [[1,2,4],[1,4,5],[1,3,1],[2,3,4],[3,4,5]], 17, 5
    edges, maxMoves, n = [[0,2,3],[0,4,4],[2,3,8],[1,3,5],[0,3,9],[3,4,6],[0,1,5],[2,4,6],[1,2,3],[1,4,1]], 8, 5
    edges, maxMoves, n = [[1,3,23],[3,5,19],[3,6,17],[1,5,14],[6,7,20],[1,4,10],[1,6,0],[3,4,20],[1,7,4],[0,4,10],[0,7,9],[2,3,3],[3,7,9],[5,7,4],[4,5,16],[0,1,16],[2,6,0],[4,7,11],[2,5,14],[5,6,22],[4,6,12],[0,6,2],[0,2,1],[2,4,22],[2,7,20]], 19, 8
    from datetime import datetime
    begin = datetime.now()
    print(sol.reachableNodes3(edges, maxMoves, n))
    print((datetime.now()- begin).total_seconds())