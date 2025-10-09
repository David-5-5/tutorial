# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def numberOfWays(self, corridor: str) -> int:
        # 自行解答
        mod = 10 ** 9 + 7
        ans, prev, cnt = 1, -1, 0
        for cur, ch in enumerate(corridor):
            if ch == 'S':
                cnt += 1
                if cnt % 2:
                    if prev > 0:ans = ans * (cur - prev) % mod
                else: prev = cur
        if cnt==0 or cnt % 2: return 0
        else: return ans
