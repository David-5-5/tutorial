class Solution:
    def largestIsland(self, grid) -> int:
        n = len(grid)
        adt = [-1] * (n ** 2)

        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]

        def union(x:int, y:int) -> int:
            '''
            union the adt and return the count of adt
            '''
            root1 = find(x)
            root2 = find(y)
            if root1 == root2:
                return -adt[root1]
            adt[root1] += adt[root2]
            adt[root2] = root1
            return -adt[root1]
        
        ans = 0
        # finish the adt
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    ans = max(1, -adt[find(i*n+j)])
                    if i - 1 >= 0 and grid[i-1][j] == 1:
                        ans = max(ans, union(i*n+j, (i-1)*n+j))
                    if j - 1 >= 0 and grid[i][j-1] == 1:
                        ans = max(ans, union(i*n+j, i*n+j-1))
        
        # try to union the island
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 0:
                    roots = set()
                    for _i, _j in [(0,1),(0,-1),(-1,0),(1,0)]:
                        if 0 <= i+_i < n and 0 <= j+_j < n and grid[i+_i][j+_j]==1:
                            roots.add(find((i+_i)*n+j+_j))
                    alt = 1
                    for root in list(roots):
                        alt -= adt[root]
                    ans = max(ans, alt)
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    grid = [[1, 0], [0, 1]]
    print(sol.largestIsland(grid))