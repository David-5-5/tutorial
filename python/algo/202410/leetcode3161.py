from typing import List

from sortedcontainers import SortedList

# 双周赛 131
class Solution:
    def getResults(self, queries: List[List[int]]) -> List[bool]:
        m = max(q[1] for q in queries) + 1
        max_t = [0] * (2 << m.bit_length()) # 
    

        # 单点更新，加上指定的数
        def update(inx:int, val:int, s:int, t:int, p:int):
            if inx == s and inx == t:
                max_t[p] = val
                return
            
            mid = (s + t) // 2
            if inx <= mid:
                update(inx, val, s, mid, p*2+1)
            if inx > mid:
                update(inx, val, mid+1, t, p*2+2)
            
            max_t[p] = max(max_t[p*2+1], max_t[p*2+2])

        # 查询区间最大值 查询区间 [0, r] 左端点固定为 0
        def query(r:int, s:int, t:int, p:int) -> int:
            if t <= r:
                return max_t[p]

            mid = (s + t) // 2

            res = query(r, s, mid, p*2+1)
            if r > mid: # mid / m
                res = max(res, query(r, mid+1, t, p*2+2))
            return res

        sl = SortedList([0, m-1]) # 哨兵
        ans = []
        for q in queries:
            inx = sl.bisect_left(q[1])
            pre = sl[inx-1] # q[1] 左侧最近的障碍物
            if q[0] == 1:
                nxt = sl[inx]
                sl.add(q[1])
                update(q[1], q[1]-pre, 0, m-1, 0)
                update(nxt, nxt - q[1], 0, m-1, 0)
            else:
                ans.append(max(query(pre, 0, m-1, 0), q[1]-pre) >= q[2])
        return ans


if __name__ == "__main__":
    sol = Solution()
    queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
    queries = [[1,1],[1,11],[1,4],[1,8],[2,13,7]]
    queries = [[1,3],[2,4,2]]
    print(sol.getResults(queries))