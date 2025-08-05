from typing import List

# 常用数据结构 - 8.1 树状数组和线段树 - 树状数组
class Solution:
    def bonus(self, n: int, leadership: List[List[int]], operations: List[List[int]]) -> List[int]:
        # 参考 oi-wiki 线段树模板 最常用的求和模板
        tree =  [0] * (4 * n)   # 树组空间
        tp = [0] * (4 * n)      # 支持懒标记

        def pushdown(s, t, p):              # 区间求和
            m = s + ((t - s) >> 1)
            tree[p*2+1] += (m - s + 1) * tp[p]
            tree[p*2+2] += (t - m) * tp[p]
            tp[p*2+1] += tp[p]
            tp[p*2+2] += tp[p]
            tp[p] = 0

        def update(l:int, r:int, value:int, s:int, t:int, p:int):
            if l <= s and t <= r:
                tree[p] += (t-s+1) * value  # 本题用于区间求和 根据题意修改
                tp[p] += value
                return
            m = s + ((t - s) >> 1)
            if tp[p] and s != t:
                pushdown(s, t, p)
            if l <= m:
                update(l, r, value, s, m, p*2+1)
            if r > m:
                update(l, r, value, m + 1, t, p*2+2)
            tree[p] = tree[p*2+1] + tree[p*2+2]
        
        def query(l, r, s, t, p):
            # [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                return tree[p]
            if tp[p] and s != t:    # 放这里安全
                pushdown(s, t, p)
            m = s + ((t - s) >> 1)
            sum = 0
            if l <= m:
                sum += query(l, r, s, m, p * 2 + 1)
            if r > m:
                sum += query(l, r, m + 1, t, p * 2 + 2)
            return sum
        # 参考 oi-wiki 线段树模板 最常用的求和模板

        
        mod = 10 ** 9 + 7
        g = [[] for _ in range(n+1)]
        for u, v in leadership:
            g[u].append(v)
            g[v].append(u)
        
        clock, clock_in, clock_out = -1, [0] * (n+1), [0] * (n+1)
        
        def dfs(u: int, fa: int) :
            nonlocal clock
            clock += 1
            clock_in[u] = clock
            for v in g[u]:
                if v == fa: continue
                dfs(v, u)
            clock_out[u] = clock
        
        dfs(1, 0)
        ans = []
        for q in operations:
            if q[0] == 3:
                l, r = clock_in[q[1]], clock_out[q[1]]
                ans.append(query(l, r, 0, n-1, 0) % mod)
            elif q[0] == 2:
                u, w = q[1], q[2]
                update(clock_in[u], clock_out[u],w, 0, n-1, 0)
            else:
                u, w = q[1], q[2]
                update(clock_in[u], clock_in[u],w, 0, n-1, 0)

        return ans        