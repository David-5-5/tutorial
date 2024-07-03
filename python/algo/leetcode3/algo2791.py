import collections
from typing import List

class Solution:
    def countPalindromePaths(self, parent: List[int], s: str) -> int:
        path_count = collections.defaultdict(int)
        g = collections.defaultdict(list)

        for i, p in enumerate(parent):
            if p < 0:continue
            g[p].append(i)

        ans = 0

        visited = set()
        def dfs(i:int, path:int):
            nonlocal ans
            path_count[path] += 1
            visited.add(i)

            for v in g[i]:
                if v not in visited:
                    new_path = path ^ (1 << (ord(s[v]) - ord('a')))
                    ans += path_count[new_path]
                    for i in range(26):
                        ans += path_count[new_path ^ 1<<i]
                    dfs(v, new_path)

        dfs(0, 0)

        return ans


