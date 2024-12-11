from collections import defaultdict
import heapq
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        # 首先思考是否先将各类型的最大值加入选择列表在补充剩下的最大值满足队列为 k，初始化为 max_distinct_categories
        # 选择 k 个建立最小堆，将最小值比较未选择的数据，并替换进队列，不断减小 distinct_categories 增大 profit
        # 但是程序不太好写
        # 参考题解，反向操作，首先将最大的profit 加入堆
        # 然后将剩余的数替换，逐渐增加 distinct_categories 并最小化减少的 profit，在这个过程中，找到最大值
        items.sort(key=lambda p:-p[0])
        cnt = defaultdict(int)
        pr = []

        res = 0
        for i in range(k):
            p, c = items[i]
            res += p
            cnt[c] += 1
            heapq.heappush(pr, (p, c))
        res += len(cnt) ** 2
        ans = res
        for p, c in items[k:]:
            # 类型已经选择，p 小于已选择类型的profit
            # distinct_categories不增加，利润下降，不会增加优雅度
            if cnt[c]: continue 

            # 对于队列中类型的数量仅为 1 的数据，不参加交换，
            # distinct_categories一增一减，抵销，而利润下降，不会增加优雅度
            while pr and cnt[pr[0][1]] == 1:
                heapq.heappop(pr)
            
            if pr:
                # 每次操作保证类型增加，利润损失最小
                pp, pc = heapq.heappop(pr) 
                cnt[pc] -= 1
                cnt[c] += 1 # 后续的值仅需要增加类型计数，不需要入堆
                dist = len(cnt)
                res += dist ** 2 - (dist-1) ** 2 + p - pp
                if res > ans : ans = res
            else:
                break

        return ans

