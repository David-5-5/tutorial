from functools import cache
from typing import List

# 贪心专题
class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        # 自行解答 贪心 + dp
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
                ans = max(score, ans)
                dfs(i+1, j)
            
            if score > 0: # 获取当前最大的token，消耗分数，获取能量
                power += tokens[j]
                score -= 1
                dfs(i, j-1)

            return ans

        return dfs(0, len(tokens)-1)        