class Solution:
    def findNumOfValidWords(self, words, puzzles) :
        letters = [set() for _ in range(26)]
        n = len(words)
        m = len(puzzles)
        for asi in range(26):
            for j in range(n):
                if words[j].find(chr(ord('a') + asi)) != -1:
                    letters[asi].add(j)

        result = [0] * m
        for i in range(m):
            first = letters[ord(puzzles[i][0])-ord('a')]
            for asi in range(26):
                if not first:
                    break
                if puzzles[i].find(chr(ord('a') + asi)) == -1:
                    first = first - letters[asi]
            result[i] = len(first)

        return result

if __name__ == "__main__":
    sol = Solution()
    words = ["aaaa","asas","able","ability","actt","actor","access"]
    puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
    print(sol.findNumOfValidWords(words, puzzles))