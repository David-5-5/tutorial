import heapq
from typing import List

# 周赛 309
class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        # 定义两个 priority queue，分别存放空闲的房间号，以及正在进行的会议
        pr1, pr2 = [i for i in range(n)], []
        res = [0] * n
        heapq.heapify(pr1)

        meetings.sort() # 按照 start 排序
        # The element is pr2 is (end, room) 表示会议结束时间，占用的会议室
        for s, e in meetings:
            while pr2 and pr2[0][0] <= s:       # 会议结束
                _, room = heapq.heappop(pr2)    # 结束会议
                heapq.heappush(pr1, room)       # 释放会议室
            
            if pr1:                             # 有空余会议室
                room = heapq.heappop(pr1)
                heapq.heappush(pr2, (e, room))
                res[room] += 1                  # 会议室使用计数增加 1
            else:                               # 无空余会议室，等待最近的end 会议结束
                end, room = heapq.heappop(pr2)
                heapq.heappush(pr2, (e+end-s, room))
                res[room] += 1

        ans = 0
        for i in range(1, n):
            if res[ans] < res[i]:ans = i
        return ans


if __name__ == "__main__":
    sol = Solution()
    n, meetings = 2, [[0,10],[1,5],[2,7],[3,4]]
    n, meetings = 3, [[1,20],[2,10],[3,5],[4,9],[6,8]]
    print(sol.mostBooked(n, meetings))