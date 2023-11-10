class Solution:
    def findWords(self, board, words) :
        words.sort()
        n, m = len(board), len(board[0])
        