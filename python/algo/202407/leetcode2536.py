from typing import List

# 周赛 328 二维差分
class Solution:
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:

        diff = [[0] * (n + 1) for _ in range(n+1)]
        for r1, c1, r2, c2 in queries:
            r2, c2 = r2+1, c2 + 1
            diff[r1][c1] += 1
            diff[r2][c1] -= 1
            diff[r1][c2] -= 1
            diff[r2][c2] += 1

        # diff = [[0] * (n) for _ in range(n)]
        # for r1, c1, r2, c2 in queries:
        #     r2, c2 = r2+1, c2 + 1
        #     diff[r1][c1] += 1
        #     if r2 < n: diff[r2][c1] -= 1
        #     if c2 < n: diff[r1][c2] -= 1
        #     if r2 < n and c2 < n: diff[r2][c2] += 1

        ans = [[0] * (n + 1) for _ in range(n+1)]
        for i in range(n):
            for j in range(n):
                ans[i+1][j+1] = ans[i][j+1] + ans[i+1][j] - ans[i][j] + diff[i][j]

        del ans[0]
        for row in ans:
            del row[0]
        
        # ans = [[0] * (n) for _ in range(n)]
        # for i in range(n):
        #     for j in range(n):
        #         ans[i][j] = (ans[i-1][j] if i>0 else 0) + (ans[i][j-1] if j>0 else 0) - \
        #               (ans[i-1][j-1] if i>0 and j>0 else 0) + diff[i][j]

        return ans
    
if __name__ == "__main__":
    solution = Solution()
    n, queries = 3, [[1,1,2,2],[0,0,1,1]]
    print(solution.rangeAddQueries(n, queries))