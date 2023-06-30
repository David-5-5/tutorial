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

    def findNumOfValidWords2(self, words, puzzles) :
        def subsets(s):
            # 初始化的子集合，默认为包含一个元素的空集合
            result = [""]
            for letter in s:
                ext = []
                for substr in result:
                    ext.append(substr + letter)
                result.extend(ext)
            return result
        
        fmask = {}
        for word in words:
            mask = 0
            for letter in word:
                mask |= 1 << (ord(letter) - ord('a'))
            if mask in fmask.keys():
                fmask[mask] += 1
            else:
                fmask[mask] = 1
        
        result = []
        for puzzle in puzzles:
            count = 0
            for subset in subsets(puzzle[1:]):
                mask = 1 << (ord(puzzle[0]) - ord('a'))
                for letter in subset:
                    mask |= 1 << (ord(letter) - ord('a'))
                if mask in fmask.keys():
                    count +=  fmask[mask]
            result.append(count)

        return result

if __name__ == "__main__":
    sol = Solution()
    words = ["aaaa","asas","able","ability","actt","actor","access"]
    puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
    print(sol.findNumOfValidWords(words, puzzles))
    print(sol.findNumOfValidWords2(words, puzzles))