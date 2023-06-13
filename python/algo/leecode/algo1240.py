class Solution:
    def tilingRectangle(self, n: int, m: int) -> int:
        def available(x, y, k):
            for i in range(k):
                for j in range(k):
                    if rect[x+i][y+j]:
                        return False
            return True

        def fillUp(x: int, y: int, k: int, val: bool) -> None:
            for i in range(k):
                for j in range(k):
                    rect[x + i][y + j] = val

        def dfs(x, y, cnt):
            nonlocal ans
            if cnt >= ans:
                return
            if x >=n:
                ans = cnt
                return
            
            if y>=m:
                dfs(x+1, 0 ,cnt)
                return
            
            if rect[x][y]:
                dfs(x, y+1, cnt)
                return

            limit = min(n-x, m-y)
            while limit >= 1 and not available(x, y, limit):
                limit -= 1
            k = limit
            while k >= 1 and available(x, y, k):
                fillUp(x, y, k, True)
                dfs(x, y + k, cnt + 1)
                fillUp(x, y, k, False)
                k -= 1

        ans = max(n,m)
        rect = [[False] * m for _ in range(n)]
        dfs(0, 0, 0)
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.tilingRectangle(20, 13))