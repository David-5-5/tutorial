from typing import Counter, List


class Solution:
    def countBlackBlocks(self, m: int, n: int, coordinates: List[List[int]]) -> List[int]:
        # 思维题，遍历每个黑格子，黑格子会出现在哪4个左上角(x,y)的 2*2的矩阵内
        # 统计 包含 1, 2，3, 4个矩阵的数量，左上角(x,y)为标识
        # 包含 0 个 矩阵的数量是所有(m-1)*(n-1)个矩阵的数 - 至少一个黑格子(1,2,3,4)矩阵数量
        ans = [0] * 5
        cnt = Counter()
        for x, y in coordinates:
            for x_, y_ in [(x - 1, y - 1), (x - 1, y), (x, y - 1), (x, y)]:
                if x_ >= 0 and x_+1 < m and y_ >= 0 and y_+1 <n:
                    cnt[n * x_ + y_] += 1
        ans[0] = (m - 1) * (n - 1) - len(cnt)
        cc = Counter(cnt.values())
        for i in range(1, 5):
            ans[i] = cc[i]
        return ans

if __name__ == "__main__":
    m, n = 3, 3
    coordinates = [[0,0],[1,1],[0,2]]
    solution = Solution()
    ans = solution.countBlackBlocks(m, n, coordinates)
    print(ans)