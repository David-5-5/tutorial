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


    def findLadders2(self, beginWord: str, endWord: str, wordList: List[str]) -> List[str]:
        # 时间复杂度 O(n * m) n = len(wordList), m = len(beginWord)
        # word 的每个字符的通配符建立单词直接的转换关系 hot 通配包括 *ot, h*t, ho*
        start, end = -1, -1
        for i in range(len(wordList)):
            if wordList[i] == beginWord: start = i
            elif wordList[i] == endWord: end = i

            if start != -1 and end != -1: break

        if end == -1: return []
        if start == -1: wordList.append(beginWord)
        
        n, m = len(wordList), len(beginWord)
        g = [[] for _ in range(n)]

        # key 通配符，val index of word in wordList
        conn = defaultdict(list)
        for i in range(n):
            w = wordList[i]
            for j in range(m):
                conn[w[:j] + '*' + w[j+1:]].append(i)
        
        # 相同的通配符之间建立图
        for u in range(n):
            w = wordList[u]
            for j in range(m):
                for v in conn[w[:j] + '*' + w[j+1:]]:
                    if u != v: g[u].append(v)

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
