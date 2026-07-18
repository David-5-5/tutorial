from collections import defaultdict
from typing import List

# 
class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[str]:
        # 时间复杂度 O(n * n * m) n = len(wordList), m = len(beginWord)
        start, end = -1, -1
        for i in range(len(wordList)):
            if wordList[i] == beginWord: start = i
            elif wordList[i] == endWord: end = i

            if start != -1 and end != -1: break

        if end == -1: return []
        if start == -1: wordList.append(beginWord)
        
        n = len(wordList)
        g = [[] for _ in range(n)]

        def isconn(u: str, v: str) -> bool:
            diff = 0
            for ch1, ch2 in zip(u, v):
                if ch1 != ch2: diff += 1
                if diff > 1: return False

            return True

        for i in range(n):
            for j in range(i+1, n):
                if isconn(wordList[i], wordList[j]):
                    g[i].append(j)
                    g[j].append(i)

        ans, vis = [], defaultdict(bool)
        vis[beginWord] = True

        def dfs(u: int) -> bool:
            if u == end:
                ans.append(wordList[u])
                return True
            for v in g[u]:
                if vis[v]: continue
                vis[v] = True
                if dfs(v):
                    ans.append(wordList[u])
                    return True
            return False

        dfs(start)
        return ans[::-1]

