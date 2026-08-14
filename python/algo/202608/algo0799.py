class Solution:
    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:
        flow = [[0] * (i+1) for i in range(query_row + 1)]
        flow[0][0] = poured
        for i in range(1, query_row + 1):
            for j in range(i+1):
                if j: flow[i][j] += max(0, flow[i-1][j-1] - 1) / 2
                if j < i: flow[i][j] += max(0, flow[i-1][j] - 1) / 2

        return min(flow[query_row][query_glass], 1)

    def champagneTower2(self, poured: int, query_row: int, query_glass: int) -> float:
        # 空间优化
        flow = [0] * (query_row + 1)
        flow[0] = poured
        for i in range(query_row):
            for j in range(i, -1, -1):
                x = flow[j] - 1
                if x > 0:
                    flow[j+1] += x / 2
                    flow[j] = x / 2
                else: flow[j] = 0.0

        return min(flow[query_glass], 1)    