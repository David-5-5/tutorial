class Solution:
    def reachingPoints(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        # 逆向思维
        def dfs(x: int, y:int) -> int:
            if x == sx and y == sy: return True
            if x < sx or y < sy: return False
            if x == sx: return (y - sy) % x == 0
            if y == sy: return (x - sx) % y == 0

            #  x >= sx y >= sy
            if x > y: return dfs(x % y, y)
            else: return dfs(x, y % x)

        return dfs(tx, ty)