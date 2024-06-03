from typing import List
class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        nSquare = n * n
        ans = []

        def addResult(ql: List[int]):
            solve = []
            for pos in ql:
                row = "".ljust(n, ".")
                row = row[0:pos%n] + 'Q' + row[pos%n + 1:]
                solve.append(row)
            ans.append(solve)

        def find(q: int, ql: List[int], cover: List[int]):
            ql.append(q)
            if len(ql) == n:
                addResult(ql)
                ql.pop(-1)
                return
            else:
                last_len = len(cover)
                x, y = q // n, q % n
                # same row
                for y_ in range(n):
                    if x*n+y_ not in cover:
                        cover.append(x*n+y_)
                # same column
                for x_ in range(n):
                    if x_*n+y not in cover:
                        cover.append(x_*n+y)
                # slope = 1
                for s_ in range(n):
                    if 0<=y-x+s_ < n and s_*n+y-x+s_ not in cover:
                        cover.append(s_*n+y-x+s_)                
                # slope = -1
                for s_ in range(n):
                    if 0<=y+x-s_ < n and s_*n+y+x-s_ not in cover:
                        cover.append(s_*n+y+x-s_)
                rem = {i for i in range(nSquare)} - set(cover)
                for next in rem:
                    if len(ql) * n <= next < (len(ql)+1) * n:
                        find(next, ql, cover)
                
                ql.pop(-1)
                del cover[last_len:]

        for i in range(n):
            find(i, [], [])
        
        return ans
    

    # refer to python/dsaa/backtracing.py
    def solveNQueens2(self, n: int) -> List[List[str]]:
        ans = []
        col = [] # col[row] = col imply queen in [row, col]

        # def isValid(r,c)->bool:
        #     for R in range(r):
        #         if R+col[R] == r+c or col[R]-R == c-r:
        #             return False
        #     return True

        def dfs(r, s):
            if r == n:
                ans.append(['.'*c + 'Q' + '.'*(n-c-1) for c in col])
                return

            for c in s:
                # if isValid(r, c):
                # As following statement equivalent to isValid method
                if all(r+c!=R+col[R] and c-r!=col[R]-R for R in range(r)):
                    col.append(c)
                    dfs(r+1, s-{c})
                    col.pop()

        dfs(0,set(range(n)))
        return ans

    def solveNQueens3(self, n: int) -> List[List[str]]:
        ans = []
        col = [0] * n  # col[row] = col imply queen in [row, col]
        onPath = [False] * n
        diag1 = [False] * (2*n-1)
        diag2 = [False] * (2*n-1)

        def dfs(r):
            if r == n:
                ans.append(['.'*c + 'Q' + '.'*(n-c-1) for c in col])
                return

            for c in range(n):
                if not onPath[c] and not diag1[r+c] and not diag2[r-c]:
                    col[r] = c
                    onPath[c] = diag1[r+c] = diag2[r-c] = True
                    dfs(r+1)
                    onPath[c] = diag1[r+c] = diag2[r-c] = False

        dfs(0)
        return ans    
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.solveNQueens(4))
    print(sol.solveNQueens3(4))