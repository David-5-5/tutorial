from collections import defaultdict
from typing import List

# 贪心专题 - 字典序最小/最大
class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        # 自行解答，使用并查集
        n = len(s)
        ans, u_sets = [''] * n, [-1] * n

        # ---Begin 模板 并查集 模板 并查集模板 for text search
        def find(x:int) -> int:
            if u_sets[x] < 0:
                return x
            else:
                u_sets[x] = find(u_sets[x])
                return u_sets[x]

        def union(u, v):
            fu = find(u)
            fv = find(v)
            if fu != fv:
                u_sets[fv] = fu
        # --- end 并查集 模板    
        
        for u, v in pairs:
            union(u,v)
        
        group = defaultdict(list)

        for i in range(n):
            fa = find(i)
            group[fa].append(i)
        
        for grp in group.values():
            sub_s = ""
            for i in grp:
                sub_s += s[i]

            for i, ch in zip(sorted(grp), sorted(sub_s)):
                ans[i] = ch
        return "".join(ans)