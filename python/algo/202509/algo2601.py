import bisect

N = 1003
is_prime = [True] * N
is_prime[0] = is_prime[1] = False
primes = []

for i in range(2, N):
    if is_prime[i]:
        primes.append(i)
        # 标记i的倍数为非质数
        for j in range(i * i, N, i):
            is_prime[j] = False


# 数学算法 - 数论 - 1.2 预处理质数（筛质数）
class Solution:
    def primeSubOperation(self, nums):
        n = len(nums)
        # 从后往前处理数组
        for i in range(n-2, -1, -1):
            if nums[i] < nums[i+1]:
                continue
            # 计算需要减小的差值
            diff = nums[i] - nums[i+1]
            # 找到第一个大于diff的质数
            idx = bisect.bisect_right(primes, diff)
            if (idx == len(primes)) :return False
            p = primes[idx]
            nums[i] -= p
            if nums[i] <= 0:
                return False
        return True