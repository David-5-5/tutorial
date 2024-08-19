from cmath import inf
from functools import lru_cache
import heapq

# 周赛 318
class Solution:
    def minimumTotalDistance(self, robot, factory) -> int:
        factory.sort(key=lambda f: f[0])
        robot.sort()
        n, m = len(factory), len(robot)
        @lru_cache(maxsize = None)
        def f(i: int, j: int) -> int:
            if j == m: return 0
            if i == n - 1:
                if m - j > factory[i][1]: return inf
                return sum(abs(x - factory[i][0]) for x in robot[j:])
            res = f(i + 1, j)
            s, k = 0, 1
            while k <= factory[i][1] and j + k - 1 < m:
                s += abs(robot[j + k - 1] - factory[i][0])
                res = min(res, s + f(i + 1, j + k))
                k += 1
            return res
        return f(0, 0)

    def minimumTotalDistance2(self, robot, factory) -> int:
        factory.sort(key=lambda f: f[0])
        robot.sort()
        m = len(robot)
        f = [0] + [inf] * m
        for pos, limit in factory:
            for j in range(m, 0, -1):
                cost = 0
                for k in range(1, min(j, limit) + 1):
                    cost += abs(robot[j - k] - pos)
                    f[j] = min(f[j], f[j - k] + cost)
        return f[m]


    def minimumTotalDistance3(self, robot, factory) -> int:
        m = len(robot)
        n = len(factory)
        robot.sort()
        factory.sort()
        # dict of repair, key is inx of factory, value is list, and 
        # it element is (-distance, inxOfRobot)
        repairs = {}

        def findNext(inxOfRobot, inxFactory):
            left = inxFactory - 1 if inxFactory else 0
            right = inxFactory + 1 if inxFactory + 1 < n else n -1
            finished = False
            while not finished:
                leftDist = 2 * (10 ** 9) if left==0 and len(repairs[left]) == factory[left][1] else abs(factory[left][0]-robot[inxOfRobot])
                rigthDist = 2 * (10 ** 9) if right == n-1 and len(repairs[right]) == factory[right][1] else abs(factory[right][0]-robot[inxOfRobot])
                if len(repairs[left]) < factory[left][1] and leftDist <= rigthDist:
                    heapq.heappush(repairs[left], (-leftDist, inxOfRobot))
                    finished = True
                elif len(repairs[right]) < factory[left][1] and leftDist >= rigthDist:
                    heapq.heappush(repairs[right], (-rigthDist, inxOfRobot))
                    finished = True
                elif len(repairs[left]) == factory[left][1] and leftDist <= rigthDist:
                    left = left - 1 if left else 0
                elif len(repairs[right]) == factory[right][1] and leftDist >= rigthDist:
                    right = right + 1 if right + 1 < n else n -1


        for i in range(n):
            repairs[i] = []
        
        curInxFactory = 0
        for i in range(m):
            dist = abs(robot[i] - factory[curInxFactory][0])
            while curInxFactory + 1 < n and dist > abs(robot[i] - factory[curInxFactory+1][0]):
                curInxFactory += 1
                dist = abs(robot[i] - factory[curInxFactory][0])
            
            if len(repairs[curInxFactory]) < factory[curInxFactory][1]:
                heapq.heappush(repairs[curInxFactory], (-dist, i))
            else:
                if repairs[curInxFactory][0][0] < -dist:
                    _, inxL = heapq.heappop(repairs[curInxFactory])
                    heapq.heappush(repairs[curInxFactory], (-dist, i))
                    findNext(inxL, curInxFactory)
                else:
                    findNext(i, curInxFactory)

        totDis = 0
        for robots in repairs.values():
            for i in range(len(robots)):
                totDis -= robots[i][0]
        
        return totDis 

if __name__ == "__main__":
    sol = Solution()
    # robot = [0,4,6]
    # factory = [[2,2],[6,2]]
    robot = [9,11,99,101]
    factory = [[10,1],[7,1],[14,1],[100,1],[96,1],[103,1]]
    print(sol.minimumTotalDistance(robot, factory))

