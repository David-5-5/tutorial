from functools import cache

# 双周赛 121
class Solution:
    def minimumOperationsToMakeEqual(self, x: int, y: int) -> int:
        # 自行解答 DP 动态规划
        @cache
        def check(cur:int):
            if cur == y: return 0
            if cur < y: return y - cur # 加 1

            res = cur - y # 减 1
            if cur%5 < (5 - cur % 5): res = min(res, cur % 5 + 1 + check(cur//5)) # - (cur % 11) 除 11
            else: res = min(res, (5 - cur % 5) + 1 +  check(cur//5 + 1)) # + 11 - (cur % 11) 除 11
            
            if cur%11 < (11 - cur % 11):res = min(res, cur % 11 + 1 + check(cur//11)) # - (cur % 11) 除 11
            else: res = min(res, (11 - cur % 11) + 1 + check(cur//11 + 1)) # + 11 - (cur % 11) 除 11

            return res

        return check(x)


if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumOperationsToMakeEqual(25, 30))