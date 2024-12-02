from typing import List


class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        # 自行解答，拓扑排序
        deg = [0] * n
        for _, v in edges:
            deg[v] += 1
        
        ans = []
        for i, d in enumerate(deg):
            if d == 0:
                ans.append(i)
        if len(ans) != 1: return -1

        return ans[0]

