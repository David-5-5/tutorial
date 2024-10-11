from cmath import inf
from collections import deque
from typing import List
class Solution:
    def findMaxValueOfEquation(self, points: List[List[int]], k: int) -> int:
        # 单调队列  对point(xi, yi) 
        # 首先确定头部出队列的要求：
        # 1. x_to_append - x_head > k, 队列head需要出队列，单调队列中, 当 i < j满足xi - xt <= k,  
        # 2. 单调队列中 t < s < .. < i < ..., i分别和头部t及s的函数值分别为xi+yi+yt-xt 和 xi+yi+ys-xs
        #    当 yt - xt >= ys - xs, 则 point t和任意后续point的函数值都会小于point s，
        #    因此point t和后续任意点的函数值都小于等于point s的函数值, 将point t出队列
        # 其次确定尾部出队列的条件，
        # 1. 对于 ... < t < ... < i , t和尾部point i及待进队列的point k的函数值分别为：xi+yi+yt-xt 和 xk+yk+yt-xt
        #    当 xi + yi <= xk + yk时，point i和前序所有点的函数都小于等于待进队列和前序的点
        # 2. 同时随着头部出队列，i及待进队列point k将逐步成为头部，因此i和待进队列point k同时满足yi - xi <= yk- xk
        #    这样避免i出队列后，和后续point的函数值大于point k和后续point的函数值
        # 函数值至少需要两个元素，因此仅当队列大于两个元素时，进行出队列操作
        ans = - float("inf")
        q = deque()
        for x, y in points:
            while q and x - q[0][0] > k:
                q.popleft()
            while len(q) > 1 and q[0][1] - q[0][0] <= q[1][1] - q[1][0]: 
                q.popleft()
            while len(q) > 1 and q[-1][0]+q[-1][1]<=x+y and q[-1][1] - q[-1][0] <= y-x:
                q.pop()
            q.append((x, y))
            if len(q) > 1:
                ans = max(ans, q[-1][1] + q[-1][0] + q[0][1] - q[0][0])
        return ans

    def findMaxValueOfEquation2(self, points: List[List[int]], k: int) -> int:
        # 2024.10 再次练习，自行解答
        q = deque() # (x, y-x) x 递增， y-x递减

        ans = -inf
        for x, y in points:
            while q and q[0][0] + k < x:
                q.popleft()
            if q: ans = max(ans, q[0][1]+y+x) # 当前记录和头部记录相加即为最大值
            while q and q[-1][1] < y-x:
                q.pop()
            q.append((x,y-x))
        return ans


if __name__ == "__main__":
    sol = Solution()
    points, k = [[-19,-12],[-13,-18],[-12,18],[-11,-8],[-8,2],[-7,12],[-5,16],[-3,9],[1,-7],[5,-4],[6,-20],[10,4],[16,4],[19,-9],[20,19]], 6
    print(sol.findMaxValueOfEquation(points, k))      
    print(sol.findMaxValueOfEquation2(points, k))   

        
