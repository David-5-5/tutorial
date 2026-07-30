from collections import defaultdict
from functools import cache
from typing import List


class Solution:
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        
        trans = defaultdict(list)
        for a in allowed:
            trans[a[:2]].append(a[2:])

        @cache
        def check(cur: str) -> bool:
            if len(cur) == 1: return True
            m = len(cur)
            
            pyramid = []
            candidate = [' '] * (m-1)

            def dfs(i: int):
                if i == m-1:
                    pyramid.append("".join(candidate))
                    return
                for ch in trans[cur[i:2+i]]:
                    candidate[i] = ch
                    dfs(i+1)
            dfs(0)

            for nxt in pyramid:
                if check(nxt): return True
            return False
        
        return check(bottom)




if __name__ == "__main__":
    print(Solution().pyramidTransition("BCD", ["BCC","CDE","CEA","FFF"]))

