class Solution:
    def removeBoxes(self, boxes) -> int:
        n = len(boxes)
        # dp[l][r][k] l~r之间，以及r之后与boxes[r]值相同的元素的个数
        dp = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
        
        def calculate(l, r, k):
            if (l > r):
                return 0
            
            # 已计算，直接返回
            if dp[l][r][k] != 0:
                return dp[l][r][k]

            # calculate
            # 初始值，计算r及后续个数
            # {6,3,6,5,6,7,6,6,8,6}
            # 初始计算 {6,3,6,5,6,7,6,6} + 1
            dp[l][r][k] = calculate(l, r-1, 0) + (k+1) ** 2

            for i in range(l, r):
                if boxes[i] == boxes[r]:
                    # 计算
                    # {6,[3,6,5,6,7,6,6,8],6}
                    # {6,3,6,[5,6,7,6,6,8],6} -> 不是最大值
                    # .... ......
                    # {6,3,6,5,6,7,6,6,[8],6} -> ..多次递归，多分枝.. -> {6,[3],6,[5],6,[7],6,6,[8],6}
                    # 其中最大值，递归到最后到 l=0,r=0,k=5
                    dp[l][r][k] = max(dp[l][r][k], calculate(l, i, k+1)+calculate(i+1, r-1, 0))
            
            return dp[l][r][k]

        return calculate(0, n-1, 0)

if __name__ == "__main__":
    sol = Solution()
    boxes = [1,3,2,2,2,3,4,3,1]
    print(sol.removeBoxes(boxes))
