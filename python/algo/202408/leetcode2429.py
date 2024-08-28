# 周赛 313
class Solution:
    def minimizeXor(self, num1: int, num2: int) -> int:
        m = num1.bit_count()
        n = num2.bit_count()
        if m == n:
            return num1
        elif m > n:
            ans, tmp = 0, num1
            k = m - n
            for _ in range(k):
                lowbit = tmp & (-tmp)
                ans |= lowbit
                tmp ^= lowbit
            return ans ^ num1
        else:
            ans= 0
            k = n - m
            for i in range(32):
                if k == 0: break
                if num1 >> i & 1 == 0:
                    ans |= 1 << i
                    k -= 1
            return ans | num1


if __name__ == "__main__":
    sol = Solution()
    num1, num2 = 1, 12
    num1, num2 = 65, 84
    print(sol.minimizeXor(num1, num2))