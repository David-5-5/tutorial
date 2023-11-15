class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList) -> int:
        if endWord not in wordList : return 0
        m = len(beginWord)
        
        begin = 0
        if beginWord not in wordList: 
            wordList.insert(0, beginWord)
        else:
            begin = wordList.index(beginWord)

        end = wordList.index(endWord)
        n = len(wordList)

        def isAdjacent(word1, word2):
            cnt = 0
            for i in range(m):
                if word1[i] != word2[i]:
                    cnt += 1
            return cnt == 1

        # 图，key is index of 
        graph = {}
        for i in range(n-1):
            for j in range(i+1, n):
                if isAdjacent(wordList[i], wordList[j]):
                    if i in graph.keys():
                        graph[i].append(j)
                    else:
                        graph[i] = [j]
                    if j in graph.keys():
                        graph[j].append(i)
                    else:
                        graph[j] = [i]

        visited = {begin}
        bfs = [(begin,1)]

        while bfs:
            v, cnt = bfs.pop(0)
            if v in graph.keys():
                for u in graph[v]:
                    if u not in visited:
                        if u == end: return cnt + 1
                        visited.add(u)
                        bfs.append((u, cnt+1))
        return 0


if __name__ == "__main__":
    sol = Solution()
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log","cog"]
    # beginWord = "talk"
    # endWord = "tail"
    # wordList = ["talk","tons","fall","tail","gale","hall","negs"]
    print(sol.ladderLength(beginWord, endWord, wordList))
    print(sol.ladderLength2(beginWord, endWord, wordList))