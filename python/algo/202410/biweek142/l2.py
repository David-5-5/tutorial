from typing import List


class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)

        new_parent = parent.copy()
        for i in range(1, n):
            anc = parent[i]
            while anc != -1:
                if s[anc] == s[i]:
                    new_parent[i] = anc
                    break
                anc = parent[anc]
        
        child = [[] for _ in range (n)]
        for i, p in enumerate(new_parent):
            if p != -1:
                child[p].append(i)

        ans = [0] * n

        def dfs(u:int) -> int:
            cnt = 1
            for v in child[u]:
                cnt += dfs(v)
            ans[u] = cnt
            return cnt
        dfs(0)
        return ans


if __name__ == "__main__":
    sol = Solution()
    parent, s = [-1,0,4,0,1],"abbba"
    parent, s  = [-1,10,0,12,10,18,11,12,2,3,2,2,2,0,4,11,4,2,0], "babadabbdabcbaceeda"
    # parent, s  = [-1,0,0,1,1,1], "abaabc"
    print(sol.findSubtreeSizes(parent, s))