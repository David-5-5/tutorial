
class Solution:
    def maximumXorProduct(self, a: int, b: int, n: int) -> int:
        # 自行解答，位运算
        MOD = 10 ** 9 + 7
        if a > b: a, b = b, a # a < b

        mx = (2 ** 50 - 1)
        for i in range(n):
            mx -= 1 << i
        
        to_avg = False
        if a & mx == b & mx:
            to_avg = True
        
        first = True
        for i in range(n-1, -1, -1):
            if a >> i & 1 == b >> i & 1: # 相等
                a |= 1 << i
                b |= 1 << i
            else: # 不等
                if not to_avg or first: 
                    a |= 1 << i
                    if b >> i & 1: b ^= 1 << i
                    if to_avg: first = False
                else:
                    b |= 1 << i
                    if a >> i & 1: a ^= 1 << i
        return (a * b) % MOD

    def maximumXorProduct2(self, a: int, b: int, n: int) -> int:
        # 位运算优化
        MOD = 10 ** 9 + 7
        if a > b: a, b = b, a # a < b

        to_avg = False
        if a & ~((1<<n)-1) == b & ~((1<<n)-1):
            to_avg = True
        
        first = True
        for i in range(n-1, -1, -1):
            if a >> i & 1 == b >> i & 1: # 相等
                a |= 1 << i
                b |= 1 << i
            else: # 不等
                if not to_avg or first: 
                    a |= 1 << i
                    b &= ~(1 << i)
                    if to_avg: first = False
                else:
                    b |= 1 << i
                    a &= ~(1 << i)
        return (a * b) % MOD


    def maximumXorProduct3(self, a: int, b: int, n: int) -> int:
        # 位运算优化
        MOD = 10 ** 9 + 7

        for i in range(n-1, -1, -1):
            if a >> i & 1 == b >> i & 1: # 相等
                a |= 1 << i
                b |= 1 << i
            else: # 不等
                if a < b:
                    a |= 1 << i
                    b &= ~(1 << i)
                else:
                    b |= 1 << i
                    a &= ~(1 << i)
        return (a * b) % MOD


if __name__ == "__main__":
    sol = Solution()
    print(sol.maximumXorProduct3(12, 5, 4))