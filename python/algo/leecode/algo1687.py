class Solution:
    def boxDelivering(self, boxes, portsCount: int, maxBoxes: int, maxWeight: int) -> int:
        n = len(boxes)
        # 转移次数的前缀和, 当前码头间的转移次数, 加上2, 包括往返仓库的次数
        # box[i-1][0] == box[i][0], 转移次数为 0
        # box[i-1][0] != box[i][0], 转移次数为 1
        deli = [0] * n
        # 箱子重量的前缀和
        weights = [0] * (n + 1)
        for i in range(n):
            weights[i+1] = boxes[i][1] + weights[i]
        for i in range(1, n):
            deli[i] += deli[i-1] + (0 if boxes[i][0]==boxes[i-1][0] else 1)

        # 状态转移方程 dp[i] = min(dp[j] + deli[i] - deli[j] + 2), 其中 j 满足：
        # i - j <= maxBoxes, 即 j >= i - maxBoxes
        # weights[i] - weights[j] <= maxWeights, 即 weights[j] >= weights[i] - maxBoxes
        dp = [0] * (n + 1)

        # 综合上述条件，因此维护一个单调递增的队列 mono 存储递增的满足条件的 j, 同时满足
        # dp[j]- deli[j] 也是单调递增
        # 若 mono 中 j0 < j1, dp[j0]- deli[j0] > dp[j1]- deli[j1] 需要选择min(dp[j]- deli[j])
        # j0在其有效期中不会被选择上，因此需要从队列中剔除，
        # 因此进行状态转移计算min(dp[j]- deli[j])，不需要比较，仅选择mono[0]中, 第一个元素 j
        mono = []
        for i in range(n):
            # dp[j]- deli[j] > 当前 dp[i]- deli[i], 从队尾出队列
            while mono and (dp[mono[-1]] - deli[mono[-1]]) >= (dp[i] - deli[i]):
                mono.pop(-1)
            mono.append(i)
            # 不满足 maxBoxes 及 maxWeight 条件的 j 从从队头出队列
            while mono and (i - mono[0] >= maxBoxes or weights[i+1] - weights[mono[0]] > maxWeight):
                mono.pop(0)
            dp[i+1] = dp[mono[0]] - deli[mono[0]] + deli[i] + 2
        return dp[n]


    def boxDelivering2(self, boxes, portsCount: int, maxBoxes: int, maxWeight: int) -> int:
        '''
        Dynamic programming
        !!!! OVERTIME !!!!!
        '''
        def count(begin, end):
            ret = 1
            cur = begin
            while cur < end:
                if boxes[cur][0] != boxes[cur+1][0]:
                    ret += 1
                cur +=1
            return ret + 1
        n = len(boxes)
        dp = [0] * (n + 1)
        weights = [0] * (n + 1)
        for i in range(n):
            weights[i+1] = boxes[i][1] + weights[i]
        
        for i in range(n):
            dp[i+1] = float("inf")
            for j in range(maxBoxes):
                if i - j < 0 or weights[i+1] - weights[i - j] > maxWeight:
                    break
                dp[i+1] = min(dp[i+1], dp[i-j] + count(i-j, i))
        return dp[n]

if __name__ == '__main__':
    sol = Solution()
    boxes = [[1,1],[2,1],[1,1]]
    portsCount, maxBoxes, maxWeight = 2, 3, 3
    # boxes = [[1,2],[3,3],[3,1],[3,1],[2,4]]
    # portsCount, maxBoxes, maxWeight = 3, 3, 6
    print(sol.boxDelivering(boxes, portsCount, maxBoxes, maxWeight))

