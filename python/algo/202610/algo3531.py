from collections import defaultdict
from typing import List


class Solution:
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:
        x_builds, y_builds = defaultdict(list[int]), defaultdict(list[int])
        for x, y in buildings:
            x_builds[x].append(y)
            y_builds[y].append(x)
        
        for _, bs in x_builds.items():
            bs.sort()

        for _, bs in y_builds.items():
            bs.sort()

        ans = 0
        for x, y in buildings:
            if len(x_builds[x]) > 2 and x_builds[x][0] != y and x_builds[x][-1] != y and \
                len(y_builds[y]) > 2 and y_builds[y][0] != x and y_builds[y][-1] != x:
                ans += 1
        return ans