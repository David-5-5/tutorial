from collections import defaultdict
from itertools import accumulate
from typing import Counter, List


class Solution:
    def maxRectangleArea(self, points: List[List[int]]) -> int:
        # O(n^5)
        # 组合四个顶点，是否可以形成矩形，并检查剩余的点是否在矩形中
        points.sort()
        n = len(points)

        rects = []
        vectex = []
        # 选择 4 个顶点的组合数
        def dfs(i:int) -> None:
            # 剪枝，剩余的数字不够
            if len(vectex) + n - i < 4: return 

            if len(vectex) == 4:
                rects.append(vectex.copy())
                return
            for j in range(i, n):
                vectex.append(j)
                dfs(j+1) # 选当前顶点后续
                vectex.pop()
        dfs(0) # 4 个顶点的组合
        
        ans = -1

        for p1, p2, p3, p4 in rects:
            if points[p1][0] == points[p2][0] and points[p3][0] == points[p4][0] and \
                points[p1][1] == points[p3][1] and points[p2][1] == points[p4][1]:
                # 形成矩形
                contain = False
                for i in (set(range(n))-set([p1,p2,p3,p4])):
                    if points[p1][0]<=points[i][0]<=points[p3][0]\
                          and points[p1][1]<=points[i][1]<=points[p2][1]:
                        contain = True # 举行内部或边上有其他点
                        break
                if not contain:
                    ans = max(ans, (points[p3][0]-points[p1][0])*(points[p2][1]-points[p1][1]))

        return ans
    

    def maxRectangleArea2(self, points: List[List[int]]) -> int:
        # 参考 TsReaper 题解
        # 取 右下和左上两个顶点，查看其他顶点位置，形成矩形，并不包含其他点
        n = len(points)
        ans = -1
        def check(xa:int, xb:int, ya:int, yb:int) -> bool:
            cnt = 0
            for k in range(n):
                # 点在矩形外
                if points[k][0] < xa or points[k][0] > xb: continue
                if points[k][1] < ya or points[k][1] > yb: continue
                if (points[k][0] == xa or points[k][0] == xb) and (points[k][1] == ya or points[k][1] == yb):
                    cnt += 1
                    continue
                return False
            return cnt == 4

        for i in range(n-1):
            for j in range(i+1, n):
                xa, xb = min(points[i][0], points[j][0]), max(points[i][0], points[j][0])
                ya, yb = min(points[i][1], points[j][1]), max(points[i][1], points[j][1])
            
                if check(xa, xb, ya, yb): ans = max(ans, (xb-xa)*(yb-ya))
        return ans

if __name__ == "__main__":
    sol = Solution()
    points = [[1,1],[1,3],[3,1],[3,3]]
    print(sol.maxRectangleArea(points))