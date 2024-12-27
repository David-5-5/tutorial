from typing import List

# 周赛 376 
class Solution:
    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        fences = [[1] + hFences + [m], [1] + vFences + [n]]
        for i in range(2): fences[i].sort()

        sides = [set(), set()]
        for k in range(2):
            length = len(fences[k])
            for i in range(length-1):
                for j in range(i+1,length):
                    sides[k].add(fences[k][j] - fences[k][i])
        
        h_side = sorted(list(sides[0]))
        v_side = sorted(list(sides[1]))

        ans = -1 
        i = j = 0
        while i < len(h_side) and j < len(v_side):
            if h_side[i] == v_side[j]:
                ans = max(ans, h_side[i] * v_side[j])
                i += 1
                j += 1
            elif h_side[i] > v_side[j]:
                j += 1
            else:
                i += 1

        return -1 if ans == -1 else ans % (10 ** 9 + 7)