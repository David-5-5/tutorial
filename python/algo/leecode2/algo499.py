from math import dist
from typing import List
from sortedcontainers import SortedDict
class Solution:
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:
        n = len(positions)
        # key is left, value is (right, height)
        ans = []
        distinct = SortedDict()
        maxh = 0
        for i in range(n):
            l = distinct.bisect_right(positions[i][0])
            r = distinct.bisect_right(positions[i][0]+positions[i][1])

            cl, cr, ch = positions[i][0], positions[i][0]+positions[i][1], positions[i][1]
            
            begin = max(0, l-1)
            bl, br, firsth, lasth, curh = -1, -1, -1, -1, 0
            tobind = []
            for t in range(begin, r):
                key, value = distinct.peekitem(t)
                tobind.append((key, value))
            
            for key, value in tobind:
                if value[0] <= cl or cr == key: # keep the leftest 
                    continue
                del distinct[key]
                if bl == -1:
                    bl = key
                    firsth = value[1]
                if t == r - 1:
                    br = value[0]
                    lasth = value[1]
                curh = max(value[1], curh)
            
            curh += ch
            maxh = max(maxh, curh)
            if bl != -1 and bl < cl:
                distinct[bl] = [cl, firsth]
            distinct[cl] = [cr, curh]
            if cr < br:
                distinct[cr] = [br, lasth]
            ans.append(maxh)

        return ans

if __name__ == "__main__":
    sol = Solution()
    positions = [[1,2],[2,3],[6,1]]
    positions = [[9,83],[1,32],[87,91],[64,61],[87,53]]
    print(sol.fallingSquares(positions))