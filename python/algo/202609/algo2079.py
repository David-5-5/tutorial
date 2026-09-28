from typing import List


class Solution:
    def wateringPlants(self, plants: List[int], capacity: int) -> int:
        ans, x = 0, -1

        left = capacity
        for i, c in enumerate(plants):
            if left >= c:
                ans += i - x
                left -= c
            else:
                ans += i + x + 2
                left = capacity - c

            x = i
        return ans

