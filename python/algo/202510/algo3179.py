# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def valueAfterKSeconds(self, n: int, k: int) -> int:
        # 暴力 O(km)
        mod = 10 ** 9 + 7
        nums = [1] * n
        for _ in range(k):
            for i in range(1, n):
                nums[i] = (nums[i] + nums[i-1]) % mod
        return nums[-1]