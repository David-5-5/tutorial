class Solution:
    def minTrioDegree(self, n: int, edges) -> int:
        from bisect import bisect_right
        graph = {}
        def put(u, v):
            if u not in graph.keys():
                graph[u] = [v]
            else:
                inx = bisect_right(graph[u], v)
                graph[u].insert(inx, v)
            if v not in graph.keys():
                graph[v] = [u]
            else:
                inx = bisect_right(graph[v], u)
                graph[v].insert(inx, u)

        for u, v in edges:
            put(u, v)

        degree = float("inf")
        for first in range(1, n+1):
            if first not in graph.keys():
                continue
            inx2 = bisect_right(graph[first], first)
            for i in range(inx2, len(graph[first])):
                second = graph[first][i]
                inx3 = bisect_right(graph[second], second)
                for j in range(inx3, len(graph[second])):
                    third = graph[second][j]
                    inx = bisect_right(graph[third], first)
                    if graph[third][inx -1] == first:
                        degree=min(degree, len(graph[first]) + len(graph[second]) + len(graph[third]) - 6)
                        if degree == 0:return 0
        
        return -1 if degree == float("inf") else degree

if __name__ == "__main__":
    sol = Solution()
    # n = 6
    # edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
    n = 17
    edges = [[12,10],[12,16],[4,9],[4,6],[14,1],[9,2],[17,6],[17,12],[8,9],[11,14],[13,5],[8,15],[13,11],[15,11],[15,14],[6,8],[12,15],[14,12],[9,1],[9,10],[10,5],[1,11],[2,10],[15,1],[7,9],[14,2],[4,1],[17,7],[3,17],[8,1],[17,13],[10,13],[8,13],[1,7],[2,6],[13,6],[7,2],[1,16],[6,3],[6,9],[16,17],[7,14]]
    print(sol.minTrioDegree(n, edges))  


