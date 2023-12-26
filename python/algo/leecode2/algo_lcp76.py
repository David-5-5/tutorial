from typing import List
class Solution:
    def getSchemeCount(self, n: int, m: int, chessboard: List[str]) -> int:
        
        points = []
        for i in range(n):
            for j in range(m):
                if chessboard[i][j] == '?':
                    points.append((i, j))
        
        others = {'.', '?'}
        def isMagic(s: str):
            if s.count('R') + s.count('B') > 2:
                next = ''
                for ch in s:
                    if ch in others:
                        continue
                    elif next != '' and next != ch:
                        return False
                    else:
                        if ch == 'R': next = 'B'
                        if ch == 'B': next = 'R'
                return True
            return False

        ans = 0
        def findNext(cnt, selected:List[str]):
            nonlocal ans
            '''path include each piont of '?'
            x, y, replace
            replace is one of '.', 'B', 'R'
            '''
            if cnt == len(points):
                ans += 1
                return
        
            for ch in ['.', 'B', 'R']:
                selected[points[cnt][0]] = selected[points[cnt][0]][0:points[cnt][1]] + ch + selected[points[cnt][0]][points[cnt][1]+1:]
                row = selected[points[cnt][0]]
                col = ""
                for i in range(n):
                    col += selected[i][points[cnt][1]]
                
                if not(isMagic(row) or isMagic(col)):
                    findNext(cnt+1, selected)

            # back trace
            selected[points[cnt][0]] = selected[points[cnt][0]][0:points[cnt][1]] + '?' + selected[points[cnt][0]][points[cnt][1]+1:]

        selected = chessboard.copy()

        findNext(0, selected)
        return ans


if __name__ == "__main__":
    sol = Solution()
    n, m, chessboard = 3, 3, ["..R","..B","?R?"]
    n, m, chessboard = 3, 3, ["?R?","B?B","?R?"]
    print(sol.getSchemeCount(n, m, chessboard))