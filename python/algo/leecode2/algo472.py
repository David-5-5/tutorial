from sortedcontainers import SortedSet

class Solution:
    def findAllConcatenatedWordsInADict(self, words):
        # Should not use list, the time complexity of count is O(n)
        # The time complexity of count of SortedSet is O(logn) 
        atoms = SortedSet()
        result = []
        
        def isConcatenated(word: str) -> bool:
            if len(atoms) < 2:return False
            
            # It must the right of a WORD, because we
            # iterate the words order by the len of word
            # So the count of full of word must be 0
            if atoms.count(word) == 1 : return True

            n = len(word)
            isCon = False
            for i in range(n):
                if atoms.count(word[0:i+1]):
                    # Check the remainder of the word
                    isCon = isConcatenated(word[i+1:])
                # If the word is concatenated then return,
                # Otherwise, match the next composited solution
                if isCon: return isCon

            return isCon
        
        # Sorted by len of word
        words.sort(key = lambda i : len(i))
        for word in words:
            if isConcatenated(word):
                result.append(word)
            else:
                atoms.add(word)

        return result

if __name__ == "__main__":
    sol = Solution()
    words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
    print(sol.findAllConcatenatedWordsInADict(words))