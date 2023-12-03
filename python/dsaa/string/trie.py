class trie_oi:
    def __init__(self):
        self.nex = [[0 for i in range(26)] for j in range(100000)]
        self.cnt = 0
        self.exist = [False] * 100000  # 该结点结尾的字符串是否存在

    def insert(self, s):  # 插入字符串
        p = 0
        for i in s:
            c = ord(i) - ord('a')
            if not self.nex[p][c]:
                self.cnt += 1
                self.nex[p][c] = self.cnt  # 如果没有，就添加结点
            p = self.nex[p][c]
        self.exist[p] = True

    def find(self, s):  # 查找字符串
        p = 0
        for i in s:
            c = ord(i) - ord('a')
            if not self.nex[p][c]:
                return False
            p = self.nex[p][c]
        return self.exist[p]
    
# !!!!!!!!!!!!!The PERFORAMCE IS VERY BAD !!!!!!!!!!!!!
# Performance compare refer to algo17.25
# !!!!!!!!!!!!!The PERFORAMCE IS VERY BAD !!!!!!!!!!!!!
class trie:
    cnt = 0
    root = None
    def __init__(self):
        self.state = self.cnt
        self.child = {}
        self.isEnd = False
        if self.state == 0:
            trie.root = self
        trie.cnt += 1

    # Insert str
    def insert(self, s):
        cur = trie.root
        for i in range(len(s)):
            if s[i] not in cur.child.keys():
                next = trie()
                cur.child[s[i]] = next
                cur = next
            else:
                cur = cur.child[s[i]]
            i += 1
        cur.isEnd = True

    # Find str
    def find(self, s):
        i, cur = 0, trie.root
        for i in range(len(s)):
            if s[i] not in cur.child.keys():
                return False
            cur = cur.child[s[i]]
            
        return cur.isEnd

# The good Trie
class Trie:
    def __init__(self):
        self.root = [{}, False]
    
    def insert(self, word):
        cur = self.root
        for c in word:
            if c not in cur[0]:
                cur[0][c] = [{}, False]
            cur = cur[0][c]
        cur[1] = True

    # Find str
    def find(self, word) :
        cur = self.root
        for c in word:
            if c not in cur[0]:
                return False, False
            cur = cur[0][c]
            
        return True, cur[1]

s = ['aa' 'aba', 'ba', 'caaa', 'cba']

oi_trie = trie_oi()
ins_trie = trie()

for word in s:
    oi_trie.insert(word)
    ins_trie.insert(word)

print(oi_trie.find('a') == ins_trie.find('a'))
print(oi_trie.find('aa') == ins_trie.find('aa'))
print(oi_trie.find('aaa') == ins_trie.find('aaa'))
print(oi_trie.find('ba') == ins_trie.find('ba'))
print(oi_trie.find('baa') == ins_trie.find('baa'))
print(oi_trie.find('caa') == ins_trie.find('caa'))
print(oi_trie.find('caaa') == ins_trie.find('caaa'))

oi_trie.insert('a')
ins_trie.insert('a')
print(oi_trie.find('a') == ins_trie.find('a'))

