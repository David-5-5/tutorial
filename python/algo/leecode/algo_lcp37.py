class Solution:
    def minRecSize(self, lines) -> float:
        # 几何题目
        # 对直线i+1, 只需考虑斜率恰好小于直线i+1的直线组中，最上方和最下方的直线
        # 因此可以考虑排序后按照斜率分组，每组保留最下方和最上方的直线，然后遍历更新
        n = len(lines)
        if n < 3: return 0

        xpoint = []
        ypoint = []
        lines.sort()

        for i in range(n):
            j = i+1 if i + 1 < n else 0
            while i != j and lines[i][0] == lines[j][0]  : 
                j = j + 1 if j + 1 < n else 0
            
            if i == j:return 0
            q = j
            while lines[q][0] == lines[j][0]:  
                x = (lines[j][1] - lines[i][1]) / (lines[i][0] - lines[j][0])
                y = x * lines[i][0] + lines[i][1]
                xpoint.append(x)
                ypoint.append(y)
                j = j + 1 if j + 1 < n else 0

        return (max(xpoint) - min(xpoint)) * (max(ypoint) - min(ypoint))


if __name__ == "__main__":
    sol = Solution()
    lines = [[2,3],[3,0],[4,1]]
    import random
    from datetime import datetime
    #lines = [[random.randint(1,10000), random.randint(-10000,10000) ] for _ in range(10 ** 3)]

    print(sol.minRecSize2(lines))
    
    lines = [[1,1],[1,7],[1,17]]
    print(sol.minRecSize2(lines))

    
    lines = [[5,2],[5,-4],[2,-5],[4,-1],[2,0]]
    print(sol.minRecSize2(lines))