# 周赛 342

class Solution:
    def sumOfMultiples(self, n: int) -> int:
        # + 3, 5, 7
        # - 3*5, 3*7 ,5*7
        # + 3 * 5 * 7
        # 自行解答
        ans = 0
        for i in range(1, n+1):
            if i % 3 == 0:
                ans += i
            elif i % 5 == 0:
                ans += i
            elif i % 7 == 0:
                ans += i
        return ans

    def sumOfMultiples2(self, n: int) -> int:
        # 参考题解
        # 使用容斥原理，通过公式计算 3, 5, 7 ，15 ，21, 35 以及 105 的和
        # n 内整除 m 的数 m, 2m, 3m, ... (n // m)*m
        # 上底 m, 下底 (n // m)*m ，高 n // m
        def s(m: int) -> int:
            return  (m + (n//m)*m) * (n//m) // 2
            # return m * (1 + (n//m)) * (n//m) // 2
        return s(3) + s(5) + s(7) - s(15) - s(21) - s(35) + s(105)
