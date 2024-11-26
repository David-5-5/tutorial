from typing import List

# 双周赛87 脑筋急转弯
class Solution:
    def minimumMoney(self, transactions: List[List[int]]) -> int:
        ans = cur = 0
        transactions.sort(key = lambda x:x[1])
        mx = 0
        for c, b in transactions:
            if c > b:  # 先亏损
                if c > cur:
                    ans += c - cur # 增加初始 money
                cur = b if c > cur else cur - c  + b # 完成当前交易后的 money
            elif c > mx: mx = c # 后盈利，仅保留盈利交易的cost最大值
        return ans + (mx-cur if mx > cur else 0)


    def minimumMoney2(self, transactions: List[List[int]]) -> int:
        # 先亏损，累积亏损值
        # 最后增加 亏损交易 cashback 和 盈利交易的 cost
        # 参考题解
        total_lose = mx = 0
        for c, b in transactions:
            if c > b:
                total_lose += c - b
                if b > mx: mx = b
            elif c > mx: mx = c
        return total_lose + mx

if __name__ == "__main__":
    sol = Solution()
    transactions = [[3,9],[0,4],[7,10],[3,5],[0,9],[9,3],[7,4],[0,0],[3,3],[8,0]]
    print(sol.minimumMoney(transactions))
    print(sol.minimumMoney2(transactions))