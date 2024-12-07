from typing import List

# 双周赛 136
class Solution:
    def minFlips(self, grid: List[List[int]]) -> int:
        # 自行解答，类似贪心，但觉得没有章法
        ans = cnt_1 = 0
        m, n = len(grid), len(grid[0])
        exist_0_1 = False
        for i in range(m//2 + m%2):
            for j in range(n//2 + n%2):
                i_p = m - i - 1
                j_p = n - j - 1

                div = 1
                if i_p == i:div <<= 1
                if j_p == j:div <<= 1

                c1 = (grid[i][j] + grid[i][j_p] + grid[i_p][j] +  grid[i_p][j_p]) // div
                c0 = 4//div - c1

                if c1 == 4: cnt_1 += c1
                elif c1 == 3: # 0 翻转为 1
                    cnt_1 += 4
                    ans += 1
                elif c1 == 2 and c0 == 2: # 0 翻转为 1
                    cnt_1 += 4
                    ans += 2
                elif c1 == 2 and c0 == 0: # 不需要翻转，如果最后仅 2 个 1，补充翻转
                    cnt_1 += 2
                elif c1 == 1: # 默认 1 翻转 为 0
                    # 存在 1 -> 0 情况，当最后 cnt % 4 = 2 情况时，0 -> 1 为最优
                    if c0 == 1: exist_0_1 = True 
                    ans += 1
        
        return (ans + 2) if cnt_1 % 4 == 2 and not exist_0_1 else ans

if __name__ == "__main__":
    sol = Solution()
    grid = [[1,0,0],[0,1,0],[0,0,1]]
    print(sol.minFlips(grid))        