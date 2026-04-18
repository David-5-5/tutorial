from typing import List, Tuple
from __future__ import annotations

class Node:
    __slots__ = 'l', 'r', 'lo', 'ro', 'cnt', 'sum'

    def __init__(self, l:int, r: int, lo:Node=None, ro:Node = None, cnt:int=0, sum:int =0):
        self.l = l
        self.r = r
        self.lo = lo
        self.ro = ro
        self.cnt = cnt
        self.sum = sum

    def maintain(self):
        self.cnt = self.lo.cnt + self.ro.cnt
        self.sum = self.lo.sum + self.ro.sum

    @staticmethod
    def build(l: int, r: int) -> Node:
        o = Node(l, r)
        if l == r: return o
        mid = (l + r) // 2
        o.lo = Node.build(l, mid)
        o.ro = Node.build(mid+1, r)

        return o

    # i 添加 al
    def add(self, rank:int, val:int) -> Node:
        o = Node(self.l, self.r, self.lo, self.ro, self.cnt, self.sum)
        if o.l == o.r:
            o.cnt +=1
            o.sum += val
            return o
        mid = (o.l + o.r) // 2
        if rank <= mid: o.lo = o.lo.add(rank, val)
        else: o.ro = o.ro.add(rank, val)
        o.maintain()
        return o

    def kth(self, prev: Node, k: int) -> int:
        if self.l == self.r: return self.l

        cnt_l = self.lo.cnt - prev.lo.cnt
        if k <= cnt_l: return self.lo.kth(prev.lo, k)
        else: return self.ro.kth(prev.ro, k-cnt_l)
    
    def query(self, prev: Node, rank: int) -> Tuple[int, int]:
        if self.r <= rank: return self.cnt - prev.cnt, self.sum - prev.sum
        cnt, sum_ = self.lo.query(prev.lo, rank)
        mid = (self.l + self.r) // 2
        if rank > mid:
            cnt_r, sum_r = self.ro.query(prev.ro, rank)
            cnt += cnt_r
            sum_ += sum_r
        return cnt, sum_

class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        left = [0] * n

        for i in range(1, n):
            left[i] = left[i-1] if nums[i] % k == nums[i-1] % k else i
        
        uni_nums = sorted(set(nums))
        val_to_rank = {num: i for i, num in enumerate(uni_nums)}

        t = [None] * (n + 1)
        t[0] = Node.build(0, len(uni_nums) - 1)

        for i, val in enumerate(nums):
            rank = val_to_rank[val]
            t[i+1] = t[i].add(rank, val)

        ans = []
        for l, r in queries:
            if left[r] > l: 
                ans.append(-1)
                continue
            
            r += 1
            seg_len = r - l
            k_rank = t[r].kth(t[l], seg_len // 2 + 1)
            median = uni_nums[k_rank]
            
            total = t[r].sum - t[l].sum
            cnt_l, sum_l = t[r].query(t[l], k_rank)
            
            s = median * cnt_l - sum_l
            s += total - sum_l - median * (seg_len - cnt_l)
            ans.append(s // k)
        return ans
        