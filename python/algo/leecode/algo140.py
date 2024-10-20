from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict) :
        # 2023 04 自行解答
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

    def wordBreak2(self, s: str, wordDict: List[str]) -> List[str]:
        # 2024 10 使用回溯模板，更加清晰
        n = len(s)
        ret = []
        # 区间划分 集合不需要 @cache
        # 区间划分数量 需要 @cache
        def dfs(l, breaks: List[str]):
            if l == n: ret.append(" ".join(breaks))

            for r in range(l+1, n+1):
                if s[l:r] in wordDict:
                    breaks.append(s[l:r])
                    dfs(r, breaks)
                    breaks.pop() # 回溯，恢复现场
        dfs(0, [])
        return ret

if __name__ == "__main__":
    sol = Solution()
    s = "catsanddog"
    wordDict = ["cat","cats","and","sand","dog"] 
    print(sol.wordBreak(s, wordDict))
    print(sol.wordBreak2(s, wordDict))