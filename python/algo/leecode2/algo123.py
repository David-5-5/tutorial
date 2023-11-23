class Solution:
    # 设置k, 兼容leetcode No. 188
    def maxProfit(self, prices, k=2) -> int:
        '''
        对于buy1而言, 在第i天我们可以不进行任何操作, 保持不变, 也可以在未进行任何操作的前提下
        以prices[i]的价格买入股票, 那么 buy1的状态转移方程即为:
        buy1=max{buy1,-prices[i]}
        对于 sell1而言, 在第i天我们可以不进行任何操作, 保持不变, 也可以在只进行过一次买操作的
        前提下以prices[i]的价格卖出股票, 那么sell1的状态转移方程即为
        sell1=max{sell1,buy1+prices[i]}
        同理: 
        buy2=max{buy2,sell1−prices[i]}
        sell2=max{sell2,buy2+prices[i]}
        '''

        '''
        我们考虑第0天时的四个状态:
        1, buy1即为以prices[0]的价格买入股票，因此 buy1=-prices[0]; 
        2, sell1即为在同一天买入并且卖出, 因此 sell1=0; 
        3, buy2即为在同一天买入并且卖出后再以prices[0]的价格买入股票, 因此 buy2=-prices[0];
        4, 同理可得 sell2=0
        '''
        buy = [-prices[0]] * k
        sell = [0] * k
        n = len(prices)

        # 从day=1开始进行动态规划
        for day in range(1, n):
            for i in range(k):
                buy[i] = max(buy[i], (0 if i == 0 else sell[i-1]) - prices[day])
                sell[i] = max(sell[i], buy[i]+prices[day])

        return max(sell)


if __name__ == "__main__":
    sol = Solution()
    prices = [3,3,5,0,0,3,1,4]
    print(sol.maxProfit(prices))
    print(sol.maxProfit(prices, 3))