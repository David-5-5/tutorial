class Solution:
    def maxDistance(self, moves: str) -> int:
        x, y, t = 0, 0, 0
        for ch in moves:
            if ch == 'U': y += 1
            elif ch == 'D': y -= 1
            elif ch == 'L': x -= 1
            elif ch == 'R': x += 1
            else: t += 1
        return abs(x) + abs(y) + t