from typing import List
from collections import defaultdict
class Solution:
    def isPrintable(self, targetGrid: List[List[int]]) -> bool:
        m, n = len(targetGrid), len(targetGrid[0])

        # The vertexs of rectangle
        # The key is color in targetGrid[i][j]
        # The value is [x1, y1, x2, y2] two vectex of key
        #   where (x1,y1) is top left corner of the rectangle
        #         (x2,y2) is bottom right corner of the rectangle
        vertexs = {}

        # The key is color
        # The value is set of cell which color rectangle contains
        # The element of set is position = i * n + j
        cells = defaultdict(lambda:set())

        # The key is color
        # The value is lack cell which color rectangle should padding
        # The element of set is position = i * n + j
        lacks = defaultdict(lambda:set())

        for i in range(m):
            for j in range(n):
                color = targetGrid[i][j]
                if color not in vertexs.keys():
                    vertexs[color] = [i, j, i, j]
                else:
                    vertexs[color] = [min(i, vertexs[color][0]), min(j, vertexs[color][1]),\
                                       max(i, vertexs[color][2]), max(j, vertexs[color][3])]
                cells[color].add(i*n+j)

        for col in vertexs.keys():
            x1, y1, x2, y2 = vertexs[col]
            complete = []
            for i in range(x1, x2+1):
                for j in range(y1, y2+1):
                    complete.append(i*n+j)
            lacks[col] = set(complete) - cells[col]

        count = m * n
        release = set()
        isRel = True
        # It is kind of toplogy sort.
        # only cell of lack in set of release, the cell of color would be released
        # The release set is empty at initial, only the complete rectangle of color, 
        # in other word, the lack of color is null, would be released
        while (isRel and len(release) != count):
            # Each loop, should color be released, otherwise it aborted.
            isRel = False
            todel = []
            for col in lacks.keys():
                if lacks[col].issubset(release):
                    isRel = True
                    release = release.union(cells[col])
                    todel.append(col)

            for col in todel:
                del lacks[col]
                del cells[col]

        if len(release) == count:
            return True
        else:
            return False


if __name__ == "__main__":
    sol = Solution()
    targetGrid = [[1,1,1],[3,1,3]]
    print(sol.isPrintable(targetGrid))