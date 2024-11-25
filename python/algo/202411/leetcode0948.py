from functools import cache
from typing import List

# 贪心专题
class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        # 自行解答 贪心 + dp O(N^2)
        if not tokens: return 0
        tokens.sort()

        ans = score = 0
        @cache
        def dfs(i:int, j:int) -> int:
            nonlocal power, ans, score
            if i > j: return

            # power > token[i]
            if power >= tokens[i]: # 获取当前最小的token开始，消耗能量，获取分数
                power -= tokens[i]
                score += 1
                ans = max(score, ans) # 产生的最大分数
                dfs(i+1, j)
            
            if score > 0: # 获取当前最大的token，消耗分数，获取能量
                power += tokens[j]
                score -= 1
                dfs(i, j-1)

            return ans

        return dfs(0, len(tokens)-1)

    def bagOfTokensScore2(self, tokens: List[int], power: int) -> int:
        # 自行解答 贪心 O(N)
        tokens.sort()

        ans = l = score = 0
        r = len(tokens) - 1
        while l <= r:
            if power >= tokens[l]: # 能获取分数尽量获取分数
                power -= tokens[l]
                score += 1
                ans = max(ans, score)
                l += 1
            elif score: # 分数>0时，当前power小于最下的token时，获取最大能量
                power += tokens[r]
                score -= 1
                r -= 1
            else: return ans
        return ans

if __name__ == "__main__":
    sol = Solution()
    tokens, power = [100,200,300,400], 200
    print(sol.bagOfTokensScore(tokens, power))