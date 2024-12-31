import heapq
from typing import List

# 周赛 327
class Solution:
    def findCrossingTime(self, n: int, k: int, time: List[List[int]]) -> int:
        # 参考题解 大模拟
        # 盲点 关于时间太理解清楚
        time.sort(key=lambda p:p[0]+p[2]) # 按照效率排序，效率越低，下标越大

        # 建立四个堆
        # 其中 wait 的元素为 (下标，时间) 下标代表效率大顶堆
        #     work 的元素为 (时间，下标) 小顶堆
        work_l, work_r, wait_r = [], [], []
        wait_l = [(-i, 0) for i in range(k)] # 工人按效率排序，效率低的优先过河
        heapq.heapify(wait_l)
        cur = 0
        # 工作顺序 wait_l -> work-r - wait_r - work_l -> loop
        while n:
            while work_l and work_l[0][0] <= cur:
                t, inx = heapq.heappop(work_l)
                heapq.heappush(wait_l, (inx, t))

            while work_r and work_r[0][0] <= cur:
                t, inx = heapq.heappop(work_r)
                heapq.heappush(wait_r, (inx, t))

            # 右侧优先过河
            if wait_r: # and wait_r[0][1] <= cur
                inx, _ = heapq.heappop(wait_r)
                cur += time[-inx][2]
                heapq.heappush(work_l, (cur+time[-inx][3], inx))
            elif wait_l: # and wait_l[0][1] <= cur
                inx, _ = heapq.heappop(wait_l)
                cur += time[-inx][0]
                heapq.heappush(work_r, (cur+time[-inx][1], inx))
                n -= 1 # 货物减少一件
            elif len(work_l) == 0:
                cur = work_r[0][0]
            elif len(work_r) == 0:
                cur = work_l[0][0]
            else:
                cur = min(work_r[0][0], work_l[0][0])

        while work_r:
            t, inx = heapq.heappop(work_r)
            cur = max(t, cur) + time[-inx][2]

        return cur