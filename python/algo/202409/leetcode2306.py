from collections import defaultdict
from itertools import combinations
from typing import List

# 周赛 297
class Solution:
    def distinctNames(self, ideas: List[str]) -> int:
        # 参考题解 - 按后缀分组 2025.1 复习
        group = defaultdict(int)

        for idea in ideas:
            # value 是后缀包含的 首字母 状态集合
            group[idea[1:]] += 1 << (ord(idea[0])-ord('a'))
        
        cnt = [[0] * 26 for _ in range(26)]
        ans = 0

        for mask in group.values():         # 遍历每个后缀
            for i in range(26):
                if mask >> i & 1 == 0:      # 后缀的首字母不包含 i
                    for j in range(26):
                        if mask >> j & 1:
                            cnt[i][j] += 1
                else:                       # 后缀的首字母包含 i
                    for j in range(26):
                        if mask >> j & 1 == 0: # i 和其他idea首字母交互，j 一定不在mask中
                            ans += cnt[i][j]   # 可以交换的数量
        
        return ans * 2

    def distinctNames2(self, ideas: List[str]) -> int:
        # 参考题解 - 按首字母分组 - 2025.1 复习 更容易理解
        group = defaultdict(set)
        for s in ideas:
            group[s[0]].add(s[1:])
        ans = 0
        for a, b in combinations(group.values(), 2):
            print(a) 
            print(b)
            m = len(a & b)
            ans += (len(a) - m) * (len(b) - m)
        return ans * 2

if __name__ == "__main__":
    sol = Solution()    
    ideas = ["coffee","donuts","time","toffee"]
    print(sol.distinctNames(ideas))
    print(sol.distinctNames2(ideas))