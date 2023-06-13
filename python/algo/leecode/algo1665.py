import heapq
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

if __name__ == '__main__':
    sol = Solution()
    tasks = [[1,1],[1,4],[1,4]]
    print(sol.minimumEffort(tasks))