from itertools import combinations
from typing import List

# 周赛 376 
class Solution:
    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        # 自行解答
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

    def maximizeSquareArea2(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        # 参考题解，太清晰了
        def f(a: List[int], mx:int) -> set[int]:
            a.extend([1, mx])
            a.sort()
            return set(y-x for x, y in combinations(a, 2))
        h_set = f(hFences, m)
        v_set = f(vFences, n)

        mx = max(h_set.intersection(v_set), default=-1)

        return -1 if mx < 0 else pow(mx, 2, 10 ** 9 + 7)