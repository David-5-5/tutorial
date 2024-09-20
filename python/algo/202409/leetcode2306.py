from collections import defaultdict
from itertools import combinations
from typing import List

# 周赛 297
class Solution:
    def distinctNames(self, ideas: List[str]) -> int:
        # 参考题解 - 按后缀分组
        group = defaultdict(int)

        for idea in ideas:
            group[idea[1:]] += 1 << (ord(idea[0])-ord('a'))
        
        cnt = [[0] * 26 for _ in range(26)]
        ans = 0

        for mask in group.values():
            for i in range(26):
                if mask >> i & 1 == 0:
                    for j in range(26):
                        if mask >> j & 1:
                            cnt[i][j] += 1
                else:
                    for j in range(26):
                        if mask >> j & 1 == 0:
                            ans += cnt[i][j]
        
        return ans * 2

    def distinctNames2(self, ideas: List[str]) -> int:
        # 参考题解 - 按首字母分组
        group = defaultdict(set)
        for s in ideas:
            group[s[0]].add(s[1:])
        ans = 0
        for a, b in combinations(group.values(), 2):
            m = len(a & b)
            ans += (len(a) - m) * (len(b) - m)
        return ans * 2

if __name__ == "__main__":
    sol = Solution()    
    ideas = ["coffee","donuts","time","toffee"]
    print(sol.distinctNames(ideas))
    print(sol.distinctNames2(ideas))