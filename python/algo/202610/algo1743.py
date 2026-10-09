from bisect import bisect_left
from collections import defaultdict
from typing import List

class Solution:
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        # 二分删除 - (与题意不符合，每个元素都不相同，因此每个节点的相邻元素的数量最多为 适用与于相同元素的情况
        n = len(adjacentPairs)
        adjs = defaultdict(list)    # key1 (key2, val) key1 = u key2 = v, val = count of key2
        for u, v in adjacentPairs:
            adjs[u].append(v)
            adjs[v].append(u)
        
        ans = [0] * (n + 1)        
        ans[0] = next(iter(adjs))
        for k, v in adjs.items():
            if len(v) % 2: ans[0] = k
            v.sort()

        for i in range(1, n+1):
            u = ans[i-1]
            v = adjs[u][-1]
            adjs[u].pop() # u 中删除 v
            idx = bisect_left(adjs[v], u)
            del adjs[v][idx] # v 中删除 v

            ans[i] = v
        return ans

    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        # list 不排序直接删除
        n = len(adjacentPairs)
        adjs = defaultdict(list)    # key1 (key2, val) key1 = u key2 = v, val = count of key2
        for u, v in adjacentPairs:
            adjs[u].append(v)
            adjs[v].append(u)
        
        ans = [0] * (n + 1)
        ans[0] = next(iter(adjs))
        for k, v in adjs.items():
            if len(v) % 2: 
                ans[0] = k
                break

        for i in range(1, n+1):
            u = ans[i-1]
            v = adjs[u][-1]
            adjs[u].pop() # u 中删除 v
            adjs[v].remove(u)

            ans[i] = v
        return ans

    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        # set 适用与于相同元素的情况
        n = len(adjacentPairs)
        adjs = defaultdict(set)    # key1 (key2, val) key1 = u key2 = v, val = count of key2
        for u, v in adjacentPairs:
            adjs[u].add(v)
            adjs[v].add(u)
        
        ans = [0] * (n + 1)
        ans[0] = next(iter(adjs))
        for k, v in adjs.items():
            if len(v) % 2: 
                ans[0] = k
                break

        for i in range(1, n+1):
            u = ans[i-1]
            v = next(iter(adjs[u]))
            adjs[u].remove(v)
            adjs[v].remove(u)

            ans[i] = v
        return ans

    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        # list 不排序不删除，在两个元素中比较，性能最佳，完美契合本题
        n = len(adjacentPairs)
        adjs = defaultdict(list) 
        for u, v in adjacentPairs:
            adjs[u].append(v)
            adjs[v].append(u)
        
        ans = [0] * (n + 1)
        ans[0] = next(iter(adjs))
        for k, v in adjs.items():
            if len(v) % 2: 
                ans[0] = k
                break
        
        prev = None
        for i in range(1, n+1):
            u = ans[i-1]
            for v in adjs[u]:
                if v != prev:
                    ans[i] = v
            prev = u
        return ans