from typing import List


class Solution:
    def countLatticePoints(self, circles: List[List[int]]) -> int:
        mx_x = max([c[0] + c[2] for c in circles])
        mx_y = max([c[1] + c[2] for c in circles])

        # circles.sort(key =lambda c:-c[2])
        ans = 0
        for i in range(mx_x+1):
            for j in range(mx_y+1):
                for x, y, r in circles:
                    if (x - i)*(x - i) + (y - j)*(y - j) <= r*r:
                        ans += 1
                        break
        return ans