import math
from typing import List
from sortedcontainers import SortedDict
class Solution:
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:
        n = len(positions)
        # key is left, value is (right, height)
        ans = []
        distinct = SortedDict()
        maxh = 0
        for i in range(n):
            l = distinct.bisect_right(positions[i][0])
            r = distinct.bisect_right(positions[i][0]+positions[i][1])

            cl, cr, ch = positions[i][0], positions[i][0]+positions[i][1], positions[i][1]
            
            begin = max(0, l-1)
            
            tobind = []
            # 找出与cl, cr可能存在交集的区间(第一个区间不确定)
            for t in range(begin, r):
                key, value = distinct.peekitem(t)
                tobind.append((key, value))
            
            # 以下值分别代表，合并后的区间左值，区间右值，合并前第一个区间的高度
            # 合并前最后一个区间的高度，所有区间的最大高度
            bl, br, firsth, lasth, curh = -1, -1, -1, -1, 0
            for key, value in tobind:
                if value[0] <= cl or cr == key: # 若第一个区间的右边界小于等于cl，跳过
                    continue
                # 删除与[cl,cr]有交集的字典，并合并为一个区间，相关值设置到如下变量中
                # bl, br, firsth, lasth, curh
                del distinct[key]
                if bl == -1:
                    bl = key
                    firsth = value[1]
                if t == r - 1:
                    br = value[0]
                    lasth = value[1]
                curh = max(value[1], curh)
            
            curh += ch # 即为当前区间的叠加后高度
            maxh = max(maxh, curh)
            if bl != -1 and bl < cl:
                distinct[bl] = [cl, firsth]
            distinct[cl] = [cr, curh]
            if cr < br:
                distinct[cr] = [br, lasth]
            ans.append(maxh)

        return ans


    def fallingSquares2(self, positions: List[List[int]]) -> List[int]:
        # 线段树的方案
        allNum = set()
        nhash = {}
        for left, side in positions:
            allNum.add(left)
            allNum.add(left+side-1)
        seq = 0
        for num in sorted(list(allNum)):
            nhash[num] = seq
            seq += 1
        
        tree =  [0] * (2 ** (math.ceil(math.log(seq, 2))+1) - 1)
        tp = [0] * (2 ** (math.ceil(math.log(seq, 2))+1) - 1)

        def pushdown(s, t, p):
            if s == t:
                tree[p] = tp[p]
            else:
                tree[p*2+1], tree[p*2+2] = tp[p], tp[p]
                tp[p*2+1], tp[p*2+2] = tp[p], tp[p]
            tp[p] = 0

        def update(l:int, r:int, value:int, s:int, t:int, p:int):
            if l <= s and t <= r:
                tree[p] = value
                tp[p] = value
                return
            m = s + ((t - s) >> 1)
            if tp[p] and s != t:
                pushdown(s, t, p)
            if l <= m:
                update(l, r, value, s, m, p*2+1)
            if r > m:
                update(l, r, value, m + 1, t, p*2+2)
            tree[p] = max(tree[p*2+1], tree[p*2+2])
        
        def query(l, r, s, t, p):
            if tp[p]:
                pushdown(s, t, p)
            # [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                return tree[p]
            m = s + ((t - s) >> 1)
            maxv = 0
            if l <= m:
                maxv = query(l, r, s, m, p * 2 + 1)
            if r > m:
                maxv = max(maxv, query(l, r, m + 1, t, p * 2 + 2))
            return maxv

        ans = []
        for left, side in positions:
            l = nhash[left]
            r = nhash[left+side-1]
            base = query(l, r, 0, seq-1, 0)
            update(l, r, base + side, 0, seq-1, 0)
            ans.append(tree[0])
        return ans

if __name__ == "__main__":
    sol = Solution()
    positions = [[1,2],[2,3],[6,1]]
    positions = [[1,6],[9,2],[1,7],[3,2],[3,5]]
    print(sol.fallingSquares(positions))
    print(sol.fallingSquares2(positions))