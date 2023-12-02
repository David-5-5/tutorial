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

if __name__ == "__main__":
    sol = Solution()
    print(sol.solveNQueens(4))