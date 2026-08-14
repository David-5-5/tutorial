class Solution:
    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:
        flow = [[0] * (i+1) for i in range(query_row + 1)]
        flow[0][0] = poured
        for i in range(1, query_row + 1):
            for j in range(i+1):
                if j: flow[i][j] += max(0, flow[i-1][j-1] - 1) / 2
                if j < i: flow[i][j] += max(0, flow[i-1][j] - 1) / 2

        return min(flow[query_row][query_glass], 1)

