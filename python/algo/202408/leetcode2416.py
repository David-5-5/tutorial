from collections import defaultdict
from typing import List

# The Trie class
class Trie:
    
    def __init__(self):
        self.children = defaultdict(Trie)
        self.score = 0
        self.ids = []
    
    def insert(self, i, word):
        cur = self
        for c in word:
            cur = cur.children[c]
            cur.score += 1
        cur.ids.append(i)
    
# 周赛 311
class Solution:
    def sumPrefixScores(self, words: List[str]) -> List[int]:
        # 参考题解
        root = Trie()
        for i, word in enumerate(words):
            root.insert(i, word)
        
        ans = [0] * len(words)

        def dfs(node:Trie, sum):
            if node is None: return
            sum += node.score

            for i in node.ids:
                ans[i] = sum
            for child in node.children.values():
                dfs(child, sum)

        dfs(root, 0)
        return ans


    
if __name__ == "__main__":
    sol = Solution()
    words = ["abc","ab","bc","b"]
    print(sol.sumPrefixScores(words))