class Solution:
    def minRecSize(self, lines) -> float:
        n = len(lines)
        if n < 3: return 0

        points = []
        
        for i in range(n-1):
            for j in range(i+1, n):
                if (lines[i][0] - lines[j][0]) == 0 : continue
                x = (lines[j][1] - lines[i][1]) / (lines[i][0] - lines[j][0])
                y = x * lines[i][0] + lines[i][1]
                points.append((x,y))

        if len(points) < 3: return 0
        orgX, orgY = points.pop(0)
        maxX, minX = orgX, orgX 
        maxY, minY = orgY, orgY

        notInLine = False
        horizontal = False
        vertical = False
        slope = 0

        for x, y in points:
            maxX = max(maxX, x)
            minX = min(minX, x)
            maxY = max(maxY, y)
            minY = min(minY, y)
            if not notInLine:
                if abs(x - orgX) < 0.1 ** -5:
                    if horizontal or slope != 0:
                        notInLine = True
                    else:
                        vertical = True
                elif abs(y - orgY) < 0.1 ** -5:
                    if vertical or slope != 0:
                        notInLine = True
                    else:
                        horizontal = True
                elif slope == 0 and not horizontal and not vertical:
                    slope = (y - orgY)/(x - orgX)
                elif abs(slope - (y - orgY)/(x - orgX)) > 0.1 ** 2:
                    notInLine = True
        return (maxX - minX) * (maxY - minY)

    def minRecSize2(self, lines) -> float:
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