from collections import defaultdict
from typing import List


class DetectSquares:

    def __init__(self):
        self.x_points = defaultdict(set)
        self.points = defaultdict(int)

    def add(self, point: List[int]) -> None:
        x, y = point[0], point[1]
        self.x_points[x].add(y)
        self.points[(x,y)] += 1

    def count(self, point: List[int]) -> int:
        res = 0
        x0, y0 = point[0], point[1]
        for y1 in self.x_points[x0]:
            if y0 == y1: continue
            x1 = x0 + (y1-y0)
            # print(x0,y0, x1, y1, self.points[(x0, y1)], self.points[(x1, y0)], self.points[(x1, y1)])
            res += self.points[(x0, y1)] * self.points[(x1, y0)] * self.points[(x1, y1)]
            x1 = x0 - (y1-y0)
            # print(x0,y0, x1, y1, self.points[(x0, y1)], self.points[(x1, y0)], self.points[(x1, y1)])
            res += self.points[(x0, y1)] * self.points[(x1, y0)] * self.points[(x1, y1)]
        return res



# Your DetectSquares object will be instantiated and called as such:
# obj = DetectSquares()
# obj.add(point)
# param_2 = obj.count(point)