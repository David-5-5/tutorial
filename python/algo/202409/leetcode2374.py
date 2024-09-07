from typing import List

# 周赛 306
class Solution:
    def edgeScore(self, edges: List[int]) -> int:
        n = len(edges)
        s, inx = -1, n+1
        score = [0] * n
        for u, v in enumerate(edges):
            score[v] += u
            if score[v] > s:
                s = score[v]
                inx = v
            elif score[v] == s and inx > v:
                inx = v
                
        return inx

if __name__ == "__main__":
    sol = Solution()
    edges = [1,0,0,0,0,7,7,5]
    print(sol.edgeScore(edges))