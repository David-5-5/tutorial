class Solution:
    def maxProfit(self, k: int, prices) -> int:
        return profit(k, prices, 0)

def profit(k:int ,prices, inx: int) -> int:
    if k == 0: return 0
    stack = []
    n  = len(prices)
    maxValue = 0
    while inx < n:
        if len(stack) == 0 or prices[inx] > stack[-1]:
            stack.append[prices[inx]]
            inx += 1
        elif len(stack) < 2 and prices[inx] <= stack[-1]:
            stack = [prices[inx]]
            inx += 1
        else:
            # finish a trade
            maxValue = max(maxValue, stack[-1]-stack[0] + profit(k-1, prices, inx))
            # 
            while stack[-1] >= prices[inx]:
                stack.pop(-1)
            stack.append(prices[inx])
            inx += 1

    maxValue = max(0, maxValue) if len(stack) < 2 else max(stack[-1] - stack[0],maxValue)
    return maxValue


if __name__ == "__main__":
    sol = Solution()
    prices = [2,4,1]
    print(sol.maxProfit(2, prices))