import heapq
class Solution:
    def getSkyline(self, buildings) :
        n = len(buildings)
        bdSet = set()
        for i in range(n):
            bdSet.add(buildings[i][0])
            bdSet.add(buildings[i][1])
        bd = list(bdSet)
        bd.sort()
        # initial local variables
        heap, output, inx, maxh = [], [], 0 ,0
        for i in range(len(bd)):
            horizon = bd[i]
            while inx < n and buildings[inx][0] <= horizon  and buildings[inx][1] > horizon:
                heapq.heappush(heap, (-buildings[inx][2],buildings[inx][1]))
                inx += 1
            # remove the element which doesn't include the horizon point
            while heap and heap[0][1] <= horizon:
                heapq.heappop(heap)
            
            if len(heap) == 0:
                maxh = 0
            else:
                maxh = -heap[0][0]
            if not output or output[-1][1] != maxh:
                output.append([horizon, maxh])
        return output

if __name__ == "__main__":
    sol = Solution()
    buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
    # buildings = [[0,2,3],[2,5,3]]
    print(sol.getSkyline(buildings))