from typing import List

# 动态规划 -  完全背包
class Solution:
    def largestNumber(self, cost: List[int], target: int) -> str:
        c_d = {}
        for i, v in enumerate(cost):
            c_d[v] = i + 1
        print(c_d)
        dp = [None] * (target + 1)
        dp[0] = []
        for k, v in sorted(c_d.items(), key=lambda p:p[1]):
            for j in range(k, target+1):
                if dp[j-k] is None: continue
                if dp[j] is None or len(dp[j-k]) + 1 >= len(dp[j]):
                    dp[j] = dp[j-k].copy()
                    dp[j].append(v)
        
        if dp[target] is None: return "0"

        return "".join([str(i) for i in reversed(dp[target])])


if __name__ == "__main__":
    sol = Solution()
    cost, target = [4,3,2,5,6,7,2,5,5], 9
    print(sol.largestNumber(cost, target))