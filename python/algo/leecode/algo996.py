class Solution:
    def numSquarefulPerms(self, nums) -> int:
        def isSquare(val : int) -> bool:
            if val == int(val ** .5) ** 2:
                return True
            else:
                return False
        
        nums.sort()
        if len(nums) == 1 and isSquare(nums):
            return 1
        elif len(nums) == 1:
            return 0
        
        if nums[0] == nums[-1] and isSquare(nums[0]+nums[-1]):
            return 1
        elif nums[0] == nums[-1]:
            return 0

        edges = []
        for i in range(len(nums)-1):
            for j in range(i, len(nums)):
                if isSquare(nums[i] + nums[j]):
                    edges.add((i,j))
        

        graph = {}
        def put(u, v):
            if u not in graph.keys():
                graph[u] = [v]
            else:
                graph[u].append(v)
            if v not in graph.keys():
                graph[v] = [u]
            else:
                graph[v].append(u)

        for u, v in edges:
            put(u, v)        

        if len(graph.keys) < len(nums) and len(edges) < len(nums)-1: return 0

        result = set()
        def dfs(i, visited):
            if i not in visited:
                visited.append(i)
                if len(visited)