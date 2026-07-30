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


    def pyramidTransition2(self, bottom: str, allowed: List[str]) -> bool:
        
        trans = defaultdict(list)
        for a in allowed:
            trans[a[:2]].append(a[2:])

        n = len(bottom)
        pyramid = [[''] * (i+1) for i in range(n)]

        for i in range(n):
            pyramid[-1][i] = bottom[i]

        vis = set()
        def dfs(i: int, j:int) -> bool:
            if i < 0: return True
            if j == len(pyramid[i]):
                # 类似实现一的 对于每行 @cache check，错误仅执行一次
                row = ''.join(pyramid[i])
                if row in vis: 
                    return False
                vis.add(row)
                
                return dfs(i-1, 0)

            bt = "".join(pyramid[i+1][j:j+2])

            for ch in trans[bt]:
                pyramid[i][j] = ch
                if dfs(i, j+1): return True
            return False
        
        return dfs(n-2, 0)



if __name__ == "__main__":
    print(Solution().pyramidTransition("BCD", ["BCC","CDE","CEA","FFF"]))

