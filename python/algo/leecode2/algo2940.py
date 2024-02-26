from typing import List
from sortedcontainers import SortedDict
class Solution:
    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        n = len(queries)
        ans = [-1] * n

        q = []
        sd = SortedDict()
        for qi, query in enumerate(queries):
            if query[0] == query[1]:
                ans[qi] = query[0]
                continue
            i, j = min(query[0], query[1]), max(query[0], query[1])
            if heights[i] < heights[j]:
                ans[qi] = j
            else:
                q.append([j, qi, heights[i]])
        q.sort()

        m = len(heights)
        for i in range(m):
            while q and q[0][0] < i:
                _, idx, val = q.pop(0)
                if val in sd.keys():
                    sd[val].append(idx)
                else:
                    sd[val] = [idx]
            inx = sd.bisect_left(heights[i])
            todel = []
            for j in range(inx):
                key, idxs = sd.peekitem(j)
                todel.append(key)
                for idx in idxs:
                    ans[idx] = i
            for key in todel:
                sd.pop(key)
        return ans

if __name__ == "__main__":
    sol = Solution()
    heights = [6,4,8,5,2,7]
    queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
    print(sol.leftmostBuildingQueries(heights, queries))