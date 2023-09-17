class Solution:
    def containVirus(self, isInfected) -> int:
        m, n = len(isInfected), len(isInfected[0])

        # The areas contains the continuous blocks of virus
        # The areas_wall contains the continuous blocks of
        # virus which have installed the wall
        # The elements of areas, areas_wall is the list of
        # position which has virus
        # position = x * n + y, 
        #   x, y is the index of isInfected
        #   n is the columns of isInfected
        _areaInx = {}
        _areas, _areas_wall = [], []

        # The element of wall is tuple(cell1, cell2)
        #   cell1 < cell2
        #   cell = x * m + y, 
        walls = set()
        
        adt = [-1] * (m*n)
        
        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]

        def union(x:int, y:int):
            '''
            union the adt and return the position
            '''
            root1, root2 = find(x), find(y)
            if root1 == root2: return

            root, child = 0, 0
            if adt[root2] < adt[root1]:
                # root 2 is deeper
                adt[root1] = root2
                root, child = root2, root1
            else:
                if adt[root2] == adt[root1]:
                    adt[root1] -= 1
                adt[root2] = root1
                root, child = root1, root2
            
            if root not in _areaInx.keys():
                _areas.append([x if root == root1 else y])
                _areaInx[root] = len(_areas) - 1

            if child not in _areaInx.keys():
                _areas[_areaInx[root]].append(y if root == root1 else x)
            else:
                _areas[_areaInx[root]].extend(_areas[_areaInx[child]])
                _areas[_areaInx[child]] = []

        # Initial the areas
        for i in range(m):
            for j in range(n):
                if j+1 < n and isInfected[i][j] == isInfected[i][j+1] == 1:
                    union(i*n+j, i*n+j+1)
                if i+1 < m and isInfected[i][j] == isInfected[i+1][j] == 1:
                    union(i*n+j, (i+1)*n+j)
                if isInfected[i][j] == 1 and find(i*n+j) not in _areaInx.keys():
                    _areas.append([i*n+j])
                    _areaInx[find(i*n+j)] = len(_areas) - 1
        
        def isWall(x, y, _x, _y):
            pos1 = x * n + y
            pos2 = (x+_x) * m + y+_y
            if (min(pos1, pos2), max(pos1, pos2)) in walls:
                return True
            else:
                return False

        def nextAreas():
            areaL, cntL, cntPosL = [], [], []

            for i in range(len(_areas)):
                cl =[]
                
                for pos in _areas[i]:
                    x, y = pos // n, pos % n
                    for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                        if 0<=x+_x<m and 0<=y+_y<n and isInfected[x+_x][y+_y]==0 and not isWall(x,y,_x,_y) and (x+_x)*n+y+_y not in cl:
                            cl.append((x+_x)*n+y+_y)
                
                areaL.append(i)
                cntL.append(len(cl))
                cntPosL.append(cl)

            return areaL, cntL, cntPosL
        
        areaI, cnt, posL = nextAreas()
        while cnt and max(cnt) > 0:
            inx = cnt.index(max(cnt))
            # install wall
            for pos in posL[inx]:
                x, y = pos // n, pos % n
                for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0<=x+_x<m and 0<=y+_y<n and (x+_x)*n+y+_y in _areas[areaI[inx]]:
                        if (min(pos, (x+_x)*n+y+_y),max(pos, (x+_x)*n+y+_y)) not in walls:
                            walls.add((min(pos, (x+_x)*n+y+_y),max(pos, (x+_x)*n+y+_y)))
            
            # clear the area of install wall
            _areas[areaI[inx]] = []
            
            # infect
            for i in range(len(posL)):
                if i == inx: continue
                for pos in posL[i]:
                    x, y = pos // n, pos % n
                    isInfected[x][y] = 1
                    for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                        if 0<=x+_x<m and 0<=y+_y<n and isInfected[x+_x][y+_y] == 1 and not isWall(x,y,_x,_y):
                            union(pos, (x+_x)*n+y+_y)

            areaI, cnt, posL = nextAreas()

        return len(walls)


    def containVirus2(self, isInfected) -> int:
        '''
        Change list to set
        '''
        m, n = len(isInfected), len(isInfected[0])

        # The _areaAdt is key/value dict
        # The key is root of adt, 
        # The value is the list which contains the continuous blocks of virus belong to root
        # The elements of value of list, is the position which has virus
        # position = x * n + y, 
        #   x, y is the index of isInfected
        #   n is the columns of isInfected
        _areaAdt = {}
        adt = [-1] * (m*n)

        # The element of wall is tuple(cell1, cell2)
        #   cell1 < cell2
        #   cell = x * m + y, 
        walls = set()
        
        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]

        def union(x:int, y:int):
            '''
            union the adt and return the position
            '''
            root1, root2 = find(x), find(y)
            if root1 == root2: return

            root, child = 0, 0
            if adt[root2] < adt[root1]:
                # root 2 is deeper
                adt[root1] = root2
                root, child = root2, root1
            else:
                if adt[root2] == adt[root1]:
                    adt[root1] -= 1
                adt[root2] = root1
                root, child = root1, root2
            
            if root not in _areaAdt.keys():
                _areaAdt[root] = [x if root == root1 else y]

            if child not in _areaAdt.keys():
                _areaAdt[root].append(y if root == root1 else x)
            else:
                _areaAdt[root].extend(_areaAdt[child])
                del _areaAdt[child]

        # Initial the areas
        for i in range(m):
            for j in range(n):
                if j+1 < n and isInfected[i][j] == isInfected[i][j+1] == 1:
                    union(i*n+j, i*n+j+1)
                if i+1 < m and isInfected[i][j] == isInfected[i+1][j] == 1:
                    union(i*n+j, (i+1)*n+j)
                if isInfected[i][j] == 1 and find(i*n+j) not in _areaAdt.keys():
                    _areaAdt[find(i*n+j)] = [i*n+j]
        
        def isWall(x, y, _x, _y):
            pos1 = x * n + y
            pos2 = (x+_x) * m + y+_y
            if (min(pos1, pos2), max(pos1, pos2)) in walls:
                return True
            else:
                return False

        def nextAreas():
            roots, cntL, cntPosL = [], [], []

            for key in _areaAdt.keys():
                cl = set()
                
                for pos in _areaAdt[key]:
                    x, y = pos // n, pos % n
                    for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                        if 0<=x+_x<m and 0<=y+_y<n and isInfected[x+_x][y+_y]==0 and not isWall(x,y,_x,_y) and (x+_x)*n+y+_y not in cl:
                            cl.add((x+_x)*n+y+_y)
                
                roots.append(key)
                cntL.append(len(cl))
                cntPosL.append(list(cl))

            return roots, cntL, cntPosL
        
        roots, cnt, posL = nextAreas()
        while cnt and max(cnt) > 0:
            inx = cnt.index(max(cnt))
            # install wall
            for pos in posL[inx]:
                x, y = pos // n, pos % n
                for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0<=x+_x<m and 0<=y+_y<n and (x+_x)*n+y+_y in _areaAdt[roots[inx]]:
                        if (min(pos, (x+_x)*n+y+_y),max(pos, (x+_x)*n+y+_y)) not in walls:
                            walls.add((min(pos, (x+_x)*n+y+_y),max(pos, (x+_x)*n+y+_y)))
            
            # clear the area of install wall
            del _areaAdt[roots[inx]]
            
            # infect
            for i in range(len(posL)):
                if i == inx: continue
                for pos in posL[i]:
                    x, y = pos // n, pos % n
                    isInfected[x][y] = 1
                    for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                        if 0<=x+_x<m and 0<=y+_y<n and isInfected[x+_x][y+_y] == 1 and not isWall(x,y,_x,_y):
                            union(pos, (x+_x)*n+y+_y)

            roots, cnt, posL = nextAreas()

        return len(walls)

if __name__ == "__main__":
    sol = Solution()
    isInfected = [[1,1,1],[1,0,1],[1,1,1]]
    # isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
    # isInfected = [[1,1,1,0,0,0,0,0,0],[1,0,1,0,1,1,1,1,1],[1,1,1,0,0,0,0,0,0]]
    isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,1,0,0,0,1],[0,0,0,0,0,0,0,1]]
    # isInfected = [[0]]
    print(sol.containVirus2(isInfected))