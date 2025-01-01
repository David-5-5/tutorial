from typing import List

# 周赛 378
class Solution:
    def canMakePalindromeQueries(self, s: str, queries: List[List[int]]) -> List[bool]:
        # 参考题解 大模拟   
        # 前缀和 + 区间分类讨论
        n = len(s)
        left, right = s[0:n//2], s[n//2:][::-1]
        pres_l = [[0] * 26 for _ in range((n//2) + 1)]
        pres_r = [[0] * 26 for _ in range((n//2) + 1)]
        pres_d = [0] * ((n//2) + 1)

        def cal_prefix_sum(t:str, pre:List[int]):
            for i in range(n//2):
                for ch in range(26):
                    pre[i+1][ch] = pre[i][ch] + (ch == ord(t[i])-ord('a'))
        
        cal_prefix_sum(left, pres_l)
        cal_prefix_sum(right, pres_r)

        for i in range(n//2):
            pres_d[i+1] = pres_d[i] +  (left[i] != right[i])
        
        def count(l:int, r:int, pres:List[List[int]]) -> List[int]:
            return [x-y for x, y in zip(pres[r+1], pres[l])]
        
        def substract(s1:List[int], s2:List[int]):
            for i, v in enumerate(s2):
                if s1[i] < v: return False
                s1[i] -= v
            return s1

        def check(l1:int, r1:int, l2:int, r2:int, pre1:List[List[int]], pre2:List[List[int]]) -> bool:
            # l1 <= l2 调用时确保 pre1 对应 [l1,r1],pre2 对应 [l2,r2]
            if pres_d[l1] > 0 or pres_d[n//2] - pres_d[max(r1,r2)+1] > 0: # 检查区间的两边是否全等
                return False
            if r2 <= r1: # 区间包含
                return count(l1,r1,pre1) == count(l1,r1,pre2)
            elif r1 < l2: # 两个不相交区间, r1 == l2 时是区间是相交的
                return pres_d[l2] - pres_d[r1+1] == 0 and \
                        count(l1,r1,pre1) == count(l1,r1,pre2) and \
                        count(l2,r2,pre1) == count(l2,r2,pre2)
            else: # l2 < r1
                # [l2, r1] 为 公共区间
                s1 = substract(count(l1,r1,pre1), count(l1,l2-1,pre2)) # l2 - 1
                s2 = substract(count(l2,r2, pre2), count(r1+1,r2,pre1)) # r1 + 1
                return s1 and s2 and s1 == s2
    
        ans = [False] * len(queries)
        for i, (l1, r1, c, d) in enumerate(queries):
            l2, r2 = n - d - 1, n - c - 1

            ans[i] = check(l1, r1, l2, r2, pres_l, pres_r) if l1 <= l2 \
                        else check(l2, r2, l1, r1, pres_r, pres_l)

        return ans