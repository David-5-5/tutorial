import heapq
from typing import List
class Solution:
    def minimumEffort(self, tasks) -> int:
        n = len(tasks)
        priory = []
        for i in range(n):
            heapq.heappush(priory, (tasks[i][1]-tasks[i][0], i))
        effort = 0
        while priory:
            _, i = heapq.heappop(priory)
            effort += tasks[i][0]
            if effort < tasks[i][1]:
                effort = tasks[i][1]
        return effort

    def minimumEffort2(self, tasks) -> int:
        n = len(tasks)
        priory = []
        for i in range(n):
            heapq.heappush(priory, (tasks[i][0]-tasks[i][1], i))
        effort = 0
        priorySec = priory.copy()
        while priory:
            _, i = heapq.heappop(priory)
            effort += tasks[i][0]
        effort += tasks[i][1] - tasks[i][0]
        
        jusity = 0
        cur = effort
        while priorySec:
            _, i = heapq.heappop(priorySec)
            jusity = max(jusity, tasks[i][1] - cur)
            cur -= tasks[i][0]
        
        effort += jusity
    
        return effort

    def minimumEffort3(self, tasks: List[List[int]]) -> int:
        # 2024.11.29
        # 贪心专题  交换论证法
        sum_act = sum(a for a, _ in tasks) # actual求和
        left, sup = sum_act, 0
        # 按照 minimum - actual 从大到小排序
        for act, mn in sorted(tasks, key=lambda p:p[0]-p[1]):
            sup = max(sup, mn - left) # 检查需要补偿的最大的数
            left -= act

        return sum_act + sup

if __name__ == '__main__':
    sol = Solution()
    tasks = [[1,1],[1,4],[1,4]]
    # tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
    print(sol.minimumEffort3(tasks))