from typing import List


class Solution:
    def placeWordInCrossword(self, board: List[List[str]], word: str) -> bool:
        m, n, t = len(board), len(board[0]), len(word)

        def check(w: str) -> bool:
            if len(w) != len(word): return False

            return all(c2 == ' ' or c1==c2 for c1, c2 in zip(word, w)) or\
                     all(c2 == ' ' or c1==c2 for c1, c2 in zip(word, w[::-1]))

        for r in range(m):
            w = ""
            for c in range(n):
                if board[r][c] == '#':
                    if check(w): return True
                    w = ""
                else: w += board[r][c]
            if check(w): return True

        for c in range(n):
            w = ""
            for r in range(m):
                if board[r][c] == '#':
                    if check(w): return True
                    w = ""
                else: w += board[r][c]
            if check(w): return True
        
        return False