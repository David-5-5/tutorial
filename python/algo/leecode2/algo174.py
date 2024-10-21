class Solution:

    def calculateMinimumHP(self, dungeon) -> int:
        ans = float("inf")

        n, m = len(dungeon), len(dungeon[0])
        cache = [(-float("inf"), -float("inf"))] * (n * m)
        
        def find(visited, sumhp, minhp):
            nonlocal ans
            x, y = visited // m, visited % m
            if x == n-1 and y == m - 1:
                ans = min(ans, max(1, 1 - minhp))
                return
            # 剪枝
            if max(1, 1 - minhp) >= ans:
                return

            if cache[visited][0] <= sumhp and cache[visited][1] <= minhp:
                cache[visited] = (sumhp, minhp)
            elif cache[visited][0] >= sumhp and cache[visited][1] >= minhp :
                return

            if y+1 < m and x+1 <n and dungeon[x][y+1] > dungeon[x+1][y]:
                find(x*m+y+1, sumhp + dungeon[x][y+1], min(minhp, sumhp + dungeon[x][y+1]))
                find((x+1)*m+y, sumhp + dungeon[x+1][y], min(minhp, sumhp + dungeon[x+1][y]))
            elif y+1 < m and x+1 <n:
                find((x+1)*m+y, sumhp + dungeon[x+1][y], min(minhp, sumhp + dungeon[x+1][y]))
                find(x*m+y+1, sumhp + dungeon[x][y+1], min(minhp, sumhp + dungeon[x][y+1]))
            elif x+1 == n:
                find(x*m+y+1, sumhp + dungeon[x][y+1], min(minhp, sumhp + dungeon[x][y+1]))
            else:
                find((x+1)*m+y, sumhp + dungeon[x+1][y], min(minhp, sumhp + dungeon[x+1][y]))

        find(0, dungeon[0][0], dungeon[0][0])
        return ans

    def calculateMinimumHP_official(self, dungeon) -> int:
        '''
        official solution
        动态规划满足“无后效性原则“，但是从左上往右下的转移的过程中，存在两个独立的参数：
        路径和(尽量大)及路径最小值（尽量大），因此无法确定中间状态。
        因此
        这样考虑从右下向左上进行动态规划 (正难反易)
        dp[i][j] 表示从坐标 (i,j) 到终点所需的最小初始值
        '''
        n, m = len(dungeon), len(dungeon[0])
        dp = [[10 ** 9]*(m+1) for _ in range(n+1)]
        
        # dp[n-1][m], dp[n][m-1]= 1, 1  # 写法一 处理边界
        dp[n-1][m-1] = max(1, 1-dungeon[n-1][m-1])  # 写法二 处理边界
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                if i == n-1 and j == m-1: continue # 写法二 处理边界
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j])

        return dp[0][0]
    
    def calculateMinimumHP_official_2(self, dungeon) -> int:
        '''
        official solution
        利用滚动数组优化一维存储空间
        '''
        n, m = len(dungeon), len(dungeon[0])
        dp = [10 ** 9]*(m+1)
        
        dp[m-1] = max(1, 1-dungeon[n-1][m-1])
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                if i == n-1 and j == m-1: continue
                dp[j] = max(1, min(dp[j], dp[j+1])-dungeon[i][j])

        return dp[0]

if __name__ == "__main__":
    sol = Solution()
    dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
    print(sol.calculateMinimumHP(dungeon))
    print(sol.calculateMinimumHP_official_2(dungeon))