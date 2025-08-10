from collections import defaultdict
from typing import List
from sortedcontainers import SortedSet

# 常用数据结构 - 8.5 动态开点线段树
class Solution:
    def kthSmallest(self, par: List[int], vals: List[int], queries: List[List[int]]) -> List[int]:
        n = len(par)
        # 构建邻接表表示树
        g = [[] for _ in range(n)]
        for i in range(1, n):
            g[par[i]].append(i)
        
        x_sum = [0] * n
        
        # 深度优先搜索计算x_sum
        def dfs(u, x):
            x_sum[u] = x ^ vals[u]
            for v in g[u]:
                dfs(v, x_sum[u])
        
        dfs(0, 0)
        
        m = len(queries)
        # 按节点分组存储查询
        qu = [[] for _ in range(n)]
        for i in range(m):
            u, k = queries[i][0], queries[i][1]
            qu[u].append((k, i))
        
        ans = [0] * m
        
        # 后序遍历处理每个节点的子树，使用启发式合并
        def post(u):
            # 创建当前节点的有序集合
            cur = SortedSet()
            cur.add(x_sum[u])
            
            for v in g[u]:
                child = post(v)
                # cur |= child # 直接求并集 超时
                
                # 启发式合并：将小集合合并到大集合中
                if len(cur) < len(child):
                    cur, child = child, cur
                # 将子集合的元素添加到当前集合
                for x in child:
                    cur.add(x)
            # 处理当前节点的所有查询
            for k, i in qu.get(u, []):
                if len(cur) < k:
                    ans[i] = -1
                else:
                    # SortedSet支持直接索引访问第k-1个元素
                    ans[i] = cur[k-1]
            
            return cur
        
        post(0)
        return ans