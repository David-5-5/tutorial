from typing import List

# 周赛 326
class Solution:
    def distinctPrimeFactors(self, nums: List[int]) -> int:

        primes = set()

        for v in nums:
            # 普通方法求每个数的质因子，自行实现，性能差
            # i = 2
            # while v > 1:
            #     while v % i == 0:
            #         v //= i
            #         primes.add(i)
            #     i += 1

            # 参考题解
            i = 2
            while i * i <=v:
                if v % i == 0:
                    primes.add(i)
                    while v % i == 0:
                        v //= i
                i += 1
            if v > 1: primes.add(v)
        return len(primes)

if __name__ == "__main__":
    sol = Solution()
    nums = [2,4,3,7,10,6]
    print(sol.distinctPrimeFactors(nums))