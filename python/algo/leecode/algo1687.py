class Solution:
    def boxDelivering(self, boxes, portsCount: int, maxBoxes: int, maxWeight: int) -> int:
        n = len(boxes)
        deli = [0] * n
        dp = [0] * (n + 1)
        weights = [0] * (n + 1)
        for i in range(n):
            weights[i+1] = boxes[i][1] + weights[i]
        for i in range(1, n):
            deli[i] += deli[i-1] + (0 if boxes[i][0]==boxes[i-1][0] else 1)
        
        mono = []
        for i in range(n):
            while mono and (dp[mono[-1]] - deli[mono[-1]]) >= (dp[i] - deli[i]):
                mono.pop(-1)
            mono.append(i)
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

