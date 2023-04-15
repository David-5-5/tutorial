class Solution:
    def boxDelivering(self, boxes, portsCount: int, maxBoxes: int, maxWeight: int) -> int:
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
    boxes = [[1,4],[1,2],[2,1],[2,1],[3,2],[3,4]]
    portsCount, maxBoxes, maxWeight = 3, 6, 7
    print(sol.boxDelivering(boxes, portsCount, maxBoxes, maxWeight))

