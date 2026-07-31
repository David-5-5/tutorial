from typing import List


class Node:
    __slots__ = 'son', 'end'

    def __init__(self):
        self.son = {}
        self.end = False

class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word:str):  # 插入字符串
        cur = self.root
        for c in word:
            if c not in cur.son:
                cur.son[c] = Node()
            cur = cur.son[c]
        cur.end = True

    def find(self, word:str) -> int:  # 查找字符串
        cur = self.root
        for c in word:
            if c not in cur.son:
                return False
            cur = cur.son[c]
            if cur.end: return True
        return False


class StreamChecker:
    def __init__(self, words: List[str]):
        self.tree = Trie()
        self.stream = ""
        for w in words:
            self.tree.insert(w[::-1])

    def query(self, letter: str) -> bool:
        self.stream += letter
        if len(self.stream) > 200: self.stream = self.stream[1:]
        return self.tree.find(self.stream[::-1])
