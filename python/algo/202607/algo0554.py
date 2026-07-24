from collections import defaultdict
from typing import List


class Solution:
    def leastBricks(self, wall: List[List[int]]) -> int:
        n, mx = len(wall), 0
        board = defaultdict(int)
        for row in wall:
            m, right = len(row), 0
            for i in range(m-1):
                right += row[i]
                board[right] += 1
                if board[right] > mx: mx = board[right]

        return n - mx