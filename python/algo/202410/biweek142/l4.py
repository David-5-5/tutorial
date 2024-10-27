from itertools import accumulate

class Solution:
    def possibleStringCount(self, word: str, k: int) -> int:
        # 参考题解
        if len(word) == k: return 1

        MOD = 10 ** 9 + 7

        word = word + '0'
        count = 1
        nums, res = [], 1
        for i in range(1, len(word)):
            if word[i-1] == word[i]:
                count += 1
            else:
                nums.append(count)
                res = (res * count) % MOD
                count = 1
        m = len(nums)
        # 若 m >= k 各段 [1~c] 的选择，乘法原理直接返回 res
        if m >= k: return res
        
        # 若 m < k 各段选择的情况，动态规划，正难则反，求小于 k 个的数量，从 k-1 开始
        # 若最后一段 m 共 c 个元素，因此可以选择 1, 2, ... c
        # 子问题就是表示 m-1 段 可以选择 k-1-j个元素 j = 1 .. c
        # 状态转移方程即为 f[m+1][k-1] = sum(f[m][k-1-j]) j = 1..c
        #               上面求和可使用前缀和进行优化
        # 初始值f[0][0] = 1
        # 各段必须选择一个因此 当 j <= i 时， f[i][j] = 0
        # 最后的答案时 res - sum(f[m][m:]) 选择的数量大于等于 m
        f = [[0]*(k) for _ in range(m+1)]
        f[0][0] = 1
        for i, c in enumerate(nums):
            presum = list(accumulate(f[i], initial=0))
            # j <= i 的 f[i][j] 都是 0, 至少选一个
            for j in range(i+1, k):
                f[i+1][j] = (presum[j] - presum[max(j-c, 0)]) % MOD
        
        return (res - sum(f[m][m:])) % MOD

        # 空间优化
        # f = [0]*(k)
        # f[0] = 1
        # for i, c in enumerate(nums):
        #     presum = list(accumulate(f, initial=0))
        #     # j <= i 的 f[j] 都是 0, 至少选一个
        #     f = [0] * (k+1)
        #     for j in range(i+1, k):
        #         f[j] = (presum[j] - presum[max(j-c, 0)]) % MOD
        
        # return (res - sum(f[m:])) % MOD

if __name__ == "__main__":
    sol = Solution()
    word, k = "aabbccdd", 7
    print(sol.possibleStringCount(word, k))