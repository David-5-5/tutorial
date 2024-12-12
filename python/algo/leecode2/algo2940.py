from typing import List
from sortedcontainers import SortedDict, SortedList

# 周赛 372
class Solution:
    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        n = len(queries)
        ans = [-1] * n

        q = SortedList()
        # 首先遍历 queries 数组
        # 情况1, queries[qi][0] == queries[qi][1], ans[i] = queries[qi][0]
        # 情况2, 若queries[qi][0/1] < queries[qi][1/0]且 heights[queries[qi][0/1]] < heights[queries[qi][1/0]]
        #       ans[i] = max(queries[qi][0],queries[qi][1])
        # 情况3, 若queries[qi][0/1] < queries[qi][1/0]且 heights[queries[qi][0/1]] > heightsqueries[qi][1/0]]
        #       将[i, max(queries[qi][0],queries[qi][1]), max(heights[queries[qi][0]],heights[queries[qi][1]])
        #       放入列表，共后续处理， qi 为queries索引， 对应到 ans 的索引
        #       在 heights 中索引及值同时大于max(queries[i][0],queries[i][1]), 
        #       max(heights[queries[i][0]],heights[queries[i][1]])的最左的值
        for qi, query in enumerate(queries):
            if query[0] == query[1]:
                ans[qi] = query[0]
                continue
            i, j = min(query[0], query[1]), max(query[0], query[1])
            if heights[i] < heights[j]:
                ans[qi] = j
            else:
                # j = max(queries[i][0],queries[i][1])
                # heights[i] = max(heights[queries[i][0]],heights[queries[i][1]])
                q.add([j, qi, heights[i]])

        m = len(heights)
        # key: 查询的高度值，value: queries中的索引列表
        sd = SortedDict()
        # 遍历 heights
        # 首先，将 q 待处理列表中 j 小于 heights 中索引 i 的值qi及height放入有序字典 sd
        # 其次，sd 中找出键值小于 heights[i] 的在 queries 中 索引 qi，其 ans 即为 i
        # 最后，删除 sd 中键值小于 heights[i] 的键 
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