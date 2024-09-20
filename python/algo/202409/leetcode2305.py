from bisect import bisect_left
from typing import List

# 周赛 297
class Solution:
    def distributeCookies(self, cookies: List[int], k: int) -> int:
        # 同 1723
        def check(limit):
            workloads = [0] * k
            return backtrack(workloads, 0, limit)

        def backtrack(workloads, i, limit):
            if i >= len(cookies):
                return True
            cur = cookies[i]
            for j in range(len(workloads)):
                if workloads[j] + cur <= limit:
                    workloads[j] += cur
                    if backtrack(workloads, i + 1, limit):
                        return True
                    workloads[j] -= cur
                # 如果当前工人未被分配工作，那么下一个工人也必然未被分配工作
                # 或者当前工作恰能使该工人的工作量达到了上限
                # 这两种情况下我们无需尝试继续分配工作                    
                if workloads[j] == 0 or workloads[j] + cur == limit:
                    break
            return False
        
        cookies.sort(reverse=True)
        l, r = max(cookies), sum(cookies)
        # while l < r:
        #     mid = (l + r) >> 1
        #     if check(cookies, k, mid):
        #         r = mid
        #     else:
        #         l = mid + 1
        # return l 
        return bisect_left(range(l, r), True, key=check) + l

    def distributeCookies2(self, cookies: List[int], k: int) -> int:
        # 状态压缩
        n = len(cookies)
        sum = [0] * (1 << n)
        for i in range(1, 1 << n):
            x = bin(i)[::-1].index('1')
            y = i - (1 << x)
            sum[i] = sum[y] + cookies[x]

        dp = [[0] * (1 << n) for _ in range(k)]
        dp[0] = sum

        for i in range(1, k):
            for j in range(1 << n):
                minn = float('inf')
                x = j # 式 1 
                while x:
                    minn = min(minn, max(dp[i - 1][j - x], sum[x]))
                    x = (x - 1) & j # 式 2 结合式 1, 遍历集合中
                dp[i][j] = minn

        return dp[k - 1][(1 << n) - 1]

if __name__ == "__main__":
    sol = Solution()
    cookies, k = [8,15,10,20,8], 2
    print(sol.distributeCookies(cookies, k)) 
    print(sol.distributeCookies2(cookies, k)) 