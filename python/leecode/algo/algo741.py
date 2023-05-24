from functools import lru_cache

class Solution:
    def cherryPickup2(self, grid) -> int:
        '''
        Local optimum is not global optimum 局部最优不是全局最优
        Execute twice Local optimum, The state transition equation is as follows:
        dp[i][j] = grid[i][j] + max(dp[i+1,j], dp[i,j+1])
        '''
        n = len(grid)

        no_way = - (n ** 2)
        @lru_cache(maxsize = None)
        def f(i, j):
            if grid[i][j] == -1: return no_way, [(i, j)]
            if i == n - 1 and j == n - 1: return grid[i][j], [(i, j)]
            if i + 1 < n and j + 1 < n:
                sum1, list1 = f(i+1, j)
                sum2, list2 = f(i, j+1)
                newsum = grid[i][j] + max(sum1,sum2)
                newlist = [(i,j)]
                if sum1 > sum2:
                    newlist.extend(list1)
                else:
                    newlist.extend(list2)
                return newsum , newlist
            elif i + 1 < n:
                sum1, list1 = f(i + 1, j)
                newsum = grid[i][j] + sum1
                newlist = [(i,j)]
                newlist.extend(list1)
                return newsum , newlist
            else:
                sum1, list1 = f(i, j + 1)
                newsum = grid[i][j] + sum1
                newlist = [(i,j)]
                newlist.extend(list1)
                return newsum , newlist
        
        ret, path = f(0, 0)
        if ret < 0:return 0

        for i, j in path:
            grid[i][j] = 0

        @lru_cache(maxsize = None)
        def f2(i, j):
            if grid[i][j] == -1: return no_way
            if i == 0 and j == 0: return grid[i][j]
            if i - 1 >= 0 and j - 1 >= 0:
                return grid[i][j] + max(f2(i-1, j),f2(i, j-1))
            elif i - 1 >= 0:
                return grid[i][j] + f2(i-1, j)
            else:
                return grid[i][j] + f2(i, j-1)

        ret += f2(n-1, n-1)
        return ret if ret > 0 else 0

    def cherryPickup(self, grid) -> int:
        '''
        Redesign the dynamic programming, simulator two person to pick up.
        The state transition equation changes as follows:
        dp[k][i][j] = max(dp[k-1][i][j], dp[k-1][i-1][j], dp[k-1][i][j-1], dp[k-1][i-1][j-1])
        i,k-i is person 1 position
        j,k-j is person 2 position
        where i = j , increase grid[i][k-i]
        where i != j, increase grid[i][k-i] + grid[j][k-j]
        '''
        n = len(grid)
        no_way = - float("inf")
        @lru_cache(maxsize = None)
        def f(k, i, j):
            if k == 0 and i == 0 and j == 0 :
                return grid[0][0]
            ret = 0
            if i == j: 
                ret += grid[i][k-i] if grid[i][k-i] >= 0 else no_way
            else:
                ret += grid[i][k-i] if grid[i][k-i] >= 0 else no_way
                ret += grid[j][k-j] if grid[j][k-j] >= 0 else no_way
            if ret < 0: return no_way
            previous = no_way
            if k-1 >= 0:
                previous = max(previous, f(k-1,i,j))
            if k-1 >=0 and i-1>=0:
                previous = max(previous, f(k-1,i-1,j))
            if k-1>=0 and j-1>=0:
                previous = max(previous, f(k-1,i,j-1))
            if k-1>=0 and i-1>=0 and j-1>=0:
                previous = max(previous, f(k-1, i-1, j-1))
            
            ret += previous
            return ret
        
        ret = f(2*n-2, n-1, n-1)

        return ret if ret >= 0 else 0


if __name__ == "__main__":
    sol = Solution()
    # grid = [[0,1,-1],[1,0,-1],[1,1,1]]
    # grid = [[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
    grid = [[1,-1,-1,-1,-1],[1,0,1,-1,-1],[0,-1,1,0,1],[1,0,1,1,0],[-1,-1,-1,1,1]]
    # grid = [[1,-1,-1,-1,-1],[1,0,1,-1,-1],[0,-1,1,0,1],[1,0,1,1,0],[-1,-1,-1,1,1]]
    # grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
    # import random
    # n = 50
    # grid = [[random.randint(0, 1) for _ in range(n)] for _ in range(n)]
    # grid[0][0], grid[n-1][n-1] = 0, 0
    print(sol.cherryPickup2(grid))