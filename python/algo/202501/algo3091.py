# 贪心专题 - 数学贪心 - 基础
class Solution:
    def minOperations(self, k: int) -> int:
        # 自行解答
        ans = 0
        val = cnt = 1
        while val * cnt < k:
            if cnt < val:
                cnt += 1
            else: val += 1
            ans += 1
        return ans