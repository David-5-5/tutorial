from typing import List

class Node:
    __slots__ = 'son', 'result'

    def __init__(self):
        self.son = [None] * 26
        self.result = 0

class Solution:
    def stringIndices(self, wordsContainer: List[str], wordsQuery: List[str]) -> List[int]:
        # 自行解答，python 内存不溢出
        root = Node()
        for i, word in enumerate(wordsContainer):
            node = root
            if len(word) < len(wordsContainer[node.result]): node.result = i

            for c in map(ord, reversed(word)):
                d = c - ord('a')
                if node.son[d] is None:
                    node.son[d] = Node()
                    node.son[d].result = i
                node = node.son[d]
                if len(word) < len(wordsContainer[node.result]):node.result = i
        
        ans = []
        for q in wordsQuery:
            node = root

            for c in map(ord, reversed(q)):
                d = c - ord('a')
                if node.son[d] is None:break
                node = node.son[d]
            ans.append(node.result)
        
        return ans