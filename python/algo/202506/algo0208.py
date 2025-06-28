# 实现一 oi wiki 模板
class Trie:
    def __init__(self):
        self.nex = [[0 for i in range(26)] for j in range(100000)]
        self.cnt = 0
        self.exist = [False] * 100000  # 该结点结尾的字符串是否存在

    def insert(self, word:str):  # 插入字符串
        p = 0
        for i in word:
            c = ord(i) - ord("a")
            if not self.nex[p][c]:
                self.cnt += 1
                self.nex[p][c] = self.cnt  # 如果没有，就添加结点
            p = self.nex[p][c]
        self.exist[p] = True

    def search(self, word:str):  # 查找字符串
        p = 0
        for i in word:
            c = ord(i) - ord("a")
            if not self.nex[p][c]:
                return False
            p = self.nex[p][c]
        return self.exist[p]

    def startsWith(self, prefix: str) -> bool:
        p = 0
        for i in prefix:
            c = ord(i) - ord("a")
            if not self.nex[p][c]:
                return False
            p = self.nex[p][c]
        return True      

# 实现二 - 参考题解，通用 性能提升
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
                return 0
            cur = cur.son[c]
        return 2 if cur.end else 1
    
    def search(self, word:str) -> bool:  # 查找字符串
        return self.find(word) == 2

    def startsWith(self, prefix: str) -> bool:
        return self.find(prefix)>0

