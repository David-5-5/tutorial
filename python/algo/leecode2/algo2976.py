from math import inf
from typing import List
import bisect
import heapq
class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        # 自行解答 使用 Dijkstra，但未使用标准模板，可读性差
        shortest = [[0 if i == j else float("inf") for i in range(26)] for j in range(26)]

        sorted_ori = [q for _, q in sorted(enumerate(original), key=lambda p:p[1])]
        sorted_ori_index = [qi for qi, _ in sorted(enumerate(original), key=lambda p:p[1])]

        def push(knowns, bfs, start, ch):
            left = bisect.bisect_left(sorted_ori, chr(ch + ord('a')))
            right = bisect.bisect_right(sorted_ori, chr(ch + ord('a')))
            for j in range(left, right):
                end = ord(changed[sorted_ori_index[j]]) - ord('a')
                cst = cost[sorted_ori_index[j]]
                if end not in knowns:
                    shortest[start][end] = min(shortest[start][end], shortest[start][ch]+cst) 
                    heapq.heappush(bfs, (shortest[start][end], end))


        for i in range(26):
            knowns = [i]
            bfs = []

            # start char
            push(knowns, bfs, i, i)
            while bfs:
                _, vertex = heapq.heappop(bfs)
                if vertex in knowns:
                    continue
                else:
                    push(knowns, bfs, i, vertex)
                knowns.append(vertex)
        
        ans = 0
        for i in range(len(source)):
            if shortest[ord(source[i])-ord('a')][ord(target[i])-ord('a')] == float("inf"):
                return -1
            ans += shortest[ord(source[i])-ord('a')][ord(target[i])-ord('a')]
        
        return ans


    def minimumCost2(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        # 参考题解 Floyd 最短路径 
        # 1334 模板
        # Begin Floyd 递推 + 降维 模板 
        w = [[0 if i == j else inf for j in range(26)] for i in range(26)] # 26 个字母
        for u, v, wt in zip(original, changed, cost):
            u, v = ord(u)-ord('a'), ord(v)-ord('a')
            # w[u][v] = w[v][u] = wt
            # 有向图, 存在多个大小不一样的同一个边
            if wt < w[u][v] : w[u][v] = wt 
        # k 范围[0,n]

        for k in range(26):
            for i in range(26):
                for j in range(26):
                    w[i][j] = min(w[i][j], w[i][k]+w[k][j])
        # End Floyd 模板

        ans = sum(w[ord(u)-ord('a')][ord(v)-ord('a')] for u, v in zip(source, target))
        return -1 if ans == inf else ans
        



if __name__ == "__main__":
    sol = Solution()
    source, target, original, changed, cost = "abcd", "acbe", ["a","b","c","c","e","d"], ["b","c","b","e","b","e"], [2,5,5,1,2,20]
    print(sol.minimumCost(source, target, original, changed, cost))
    print(sol.minimumCost2(source, target, original, changed, cost))