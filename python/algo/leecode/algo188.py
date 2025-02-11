from math import inf
from functools import cache
def profit(k:int ,prices, inx: int, visited) -> int:
    if k == 0: return 0
    if (k, inx) in visited.keys(): return visited[(k, inx)]
    stack = []
    n  = len(prices)
    cur = inx
    maxVal = 0
    while cur < n:
        if len(stack) == 0 or prices[cur] > stack[-1]:
            stack.append(prices[cur])
            cur += 1
        elif len(stack) < 2 and prices[cur] <= stack[-1]:
            stack = [prices[cur]]
            cur += 1
        else:
            # finish a trade
            maxVal = max(maxVal, stack[-1]-stack[0] + profit(k-1, prices, cur, visited))
            
            while stack and stack[-1] >= prices[cur]:
                stack.pop(-1)
            stack.append(prices[cur])
            cur += 1
    
    maxVal = max(0, maxVal) if len(stack) < 2 else max(stack[-1] - stack[0],maxVal)
    visited[(k, inx)] = maxVal
    return maxVal

class Solution:
    def maxProfit(self, k: int, prices) -> int:
        visited = {}

        @cache
        def profit(k:int, inx: int) -> int:
            if k == 0: return 0
            if (k, inx) in visited.keys(): return visited[(k, inx)]
            stack = []
            n  = len(prices)
            cur = inx
            maxVal = 0
            while cur < n:
                if len(stack) == 0 or prices[cur] > stack[-1]:
                    stack.append(prices[cur])
                    cur += 1
                elif len(stack) < 2 and prices[cur] <= stack[-1]:
                    stack = [prices[cur]]
                    cur += 1
                else:
                    # finish a trade
                    maxVal = max(maxVal, stack[-1]-stack[0] + profit(k-1, cur))
                    
                    while stack and stack[-1] >= prices[cur]:
                        stack.pop(-1)
                    stack.append(prices[cur])
                    cur += 1
            
            maxVal = max(0, maxVal) if len(stack) < 2 else max(stack[-1] - stack[0],maxVal)
            visited[(k, inx)] = maxVal
            return maxVal

        val = profit(k, 0)
        return val

    def maxProfit2(self, k: int, prices) -> int:
        '''
        找出最大最多可能的交易
        其规则是：
        1、若进栈的当前价格小于栈中唯一的值, 则更新栈中价格,取最小的可能成交价格
        2、队列中仅保留当前最小的交易价格和当前最高价格, 若后续队列单调递增,则不断更新栈尾的最高价格，
          若遇到小于栈尾的价格,则,栈中队首和对尾即完成一交易。并将当前价格进栈
        如果候选的交易数量小于等于K, 则交易的收益为最大收益
        如果候选的交易数量大于K, 找出后续交易可以合并的交易, 同时合并后的损失最小, 直至满足交易数量K
        '''
        n = len(prices)
        candidate = []
        stack = []
        for i in range(n):
            if not stack:
                stack = [prices[i]]
            elif len(stack) == 1 and prices[i] > stack[-1]:
                stack.append(prices[i])
            elif len(stack) == 1:
                stack = [prices[i]]
            elif len(stack) == 2 and prices[i]>=stack[-1]:
                stack.pop(-1)
                stack.append(prices[i])
            else:
                candidate.append((stack[0], stack[1]))
                stack = [prices[i]]

        if len(stack) == 2: candidate.append((stack[0], stack[1]))

        def mergeCandi() -> int:
            '''
            交易合并由三种情况，举例说明：
            情况1 (1, 6) (2, 5) 保留交易1 减少交易收入3
            情况2 (6, 8) (1, 4) 保留交易2 减少交易收入2
            情况3 (1, 6) (3, 7) 合并交易为 (1, 7) 减少建议收入3
            '''
            while len(candidate) > k:
                n = len(candidate)
                merges = []
                for i in range(0, n-1):
                    # The lost of merge i and i + 1
                    trade1 = candidate[i][1] - candidate[i][0]
                    trade2 = candidate[i+1][1] - candidate[i+1][0]
                    merged = candidate[i][1] - candidate[i+1][0]
                    merges.append((min(trade1, trade2, merged), i))
                import heapq
                heapq.heapify(merges)
                # 使用优先队列，找出损失最小的交易进行合并
                # 每次合并一次
                _, inx = heapq.heappop(merges)
                trade1 = candidate[inx][1] - candidate[inx][0]
                trade2 = candidate[inx+1][1] - candidate[inx+1][0]
                merged = candidate[inx][1] - candidate[inx+1][0]
                if trade1 == min(trade1, trade2, merged):
                    candidate[inx] = (candidate[inx+1][0], candidate[inx+1][1])
                elif merged == min(trade1, trade2, merged):
                    candidate[inx] = (candidate[inx][0], candidate[inx+1][1])
                candidate.pop(inx+1)

        mergeCandi()
        ret = 0
        for trade in candidate:
            ret += (trade[1] - trade[0])
        return ret

    from typing import List
    # From algo 122, add condition, tranactions <= k
    # 状态转移方程增加 一个状态 j 不超过 k
    # dfs(i, j, False) = max(dfs(i-1, j, False),                不变化
    #                        dfs(i-1, j-1 True) + prices[i])    卖掉股票
    # dfs(i, j, True) = max(dfs(i-1, j, True),                  不变化
    #                       dfs(i-1, j, False) - prices[i])     买入股票
    # 注：状态转移，等号左边是后一个状态，右边是前一个状态
    def maxProfit3(self, k: int, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i:int,j:int, hold:bool):
            if j < 0: return -inf
            if i < 0:
                return -inf if hold else 0
            if hold:
                return max(dfs(i-1,j,True), dfs(i-1, j, False)-prices[i])
            return max(dfs(i-1, j, False), dfs(i-1, j-1, True) + prices[i])

        return dfs(n-1, k, False)

if __name__ == "__main__":
    sol = Solution()
    k, prices =1, [3,3,5,0,0,3,1,4]
    from datetime import datetime
    begin = datetime.now()
    print(sol.maxProfit2(k, prices))
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    print(sol.maxProfit3(k, prices))
    print((datetime.now()- begin).total_seconds())

