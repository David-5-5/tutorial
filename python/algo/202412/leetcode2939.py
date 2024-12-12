
class Solution:
    def maximumXorProduct(self, a: int, b: int, n: int) -> int:
        # 自行解答，位运算
        # 最初的思路，求 (a XOR X) * (b XOR X) 的最大值 按位比较 a b，
        #   相同，则 a，b 同时设置为 1
        #   不同，则 将第一个不同位 1 设置到 a 上，其余不同位 1 设置到 b 上，确保 a b 的差尽量小
        #        不同位上的数字分配到 a b 上，这样乘积是最大的
        #        分两种情况判断：
        #           第一种情况，a b 的最高位一样或在n的范围内，将不同的数字平均分配到 a b上
        #           第二种情况，a b 的最高位不一样且在n范围外，将所用数字分配到小的数字上
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
        # 位运算优化，思路同 maximumXorProduct 优化了位运算的添加元素/删除元素操作
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
                    a |= 1 << i     # 将元素 i 加入集合
                    b &= ~(1 << i)  # 将元素 i 移出集合
                    if to_avg: first = False
                else:
                    b |= 1 << i
                    a &= ~(1 << i)
        return (a * b) % MOD


    def maximumXorProduct3(self, a: int, b: int, n: int) -> int:
        # 去掉不必要的情况判断，在位不同的时候，把元素添加到小的数字中即可
        # 优化后代码如下
        MOD = 10 ** 9 + 7

        for i in range(n-1, -1, -1):
            if a >> i & 1 == b >> i & 1: # 相等
                a |= 1 << i
                b |= 1 << i
            else: # 不等
                if a < b:   # 尽量向小的数中增加值
                    a |= 1 << i     # 将元素 i 加入集合
                    b &= ~(1 << i)  # 将元素 i 移出集合
                else:
                    b |= 1 << i
                    a &= ~(1 << i)
        return (a * b) % MOD


if __name__ == "__main__":
    sol = Solution()
    print(sol.maximumXorProduct3(12, 5, 4))