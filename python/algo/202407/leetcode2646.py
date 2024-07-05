from collections import defaultdict
from functools import cache
from typing import List


class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        # 自行解答

        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        p_sum = defaultdict(int)
        
        # 计算每个trip经过的节点，并统计数量，为后续计算总价提供所有访问节点及其数量
        def dfs(s:int, e: int, path:List[int], visited: List[bool]) -> bool:
            visited[s] = True
            if s == e:
                return True
            
            for v in graph[s]:
                if visited[v]: continue
                path.append(v)
                if dfs(v, e, path, visited):
                    return True
                path.pop()
        
        for s, e in trips:
            path = [s]
            visited = [False] * n
            dfs(s, e, path, visited)
            for v in path:
                p_sum[v] += 1
        
        
        # 遍历所有节点，计算总价，并返回最小值
        visited = [False] * n
        visited[0] = True
        @cache
        def calculate(x:int, father:bool) -> int:
            '''
            x: 当前访问的节点
            father: x 的父节点是否半价 True 表示半价, False 表示原价
            
            因此当 x 的父节点是半价时, x 的价格只能为全价
            当 x 的父节点是原价时, x 的价格可以为全价 或 半价
            '''
            res = price[x] * p_sum[x]
            res2 = price[x]// 2 * p_sum[x]
            for v in graph[x]:
                if visited[v]: continue

                visited[v] = True
                res += calculate(v, False)
                if not father:
                    res2 += calculate(v, True)
                visited[v] = False

            if father:
                return res
            else:
                return min(res, res2)


        return calculate(0, False)
    
