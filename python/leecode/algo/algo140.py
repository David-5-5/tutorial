class Solution:
    def wordBreak(self, s: str, wordDict) :
        n = len(s)
        ret = []
        
        def findNext(breaks, inx):
            for word in wordDict:
                cur = breaks.copy()
                if inx == s.find(word, inx):
                    cur.append(word)
                    if inx + len(word) == n:
                        ret.append(" ".join(cur))
                    else:
                        findNext(cur, inx + len(word))
        findNext([], 0)
        return ret

if __name__ == "__main__":
    sol = Solution()
    s = "catsanddog"
    wordDict = ["cat","cats","and","sand","dog"] 
    print(sol.wordBreak(s, wordDict))