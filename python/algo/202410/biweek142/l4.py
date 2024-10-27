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
        if m >= k: return res
        
        # f = [[0]*(k+1) for _ in range(m+1)]
        # f[0][0] = 1
        # for i, c in enumerate(nums):
        #     presum = list(accumulate(f[i], initial=0))
        #     # j <= i 的 f[i][j] 都是 0, 至少选一个
        #     for j in range(i+1, k):
        #         f[i+1][j] = (presum[j] - presum[max(j-c, 0)]) % MOD
        
        # return (res - sum(f[m][m:])) % MOD

        f = [0]*(k+1)
        f[0] = 1
        for i, c in enumerate(nums):
            presum = list(accumulate(f, initial=0))
            # j <= i 的 f[j] 都是 0, 至少选一个
            f = [0] * (k+1)
            for j in range(i+1, k):
                f[j] = (presum[j] - presum[max(j-c, 0)]) % MOD
        
        return (res - sum(f[m:])) % MOD

if __name__ == "__main__":
    sol = Solution()
    word, k = "aabbccdd", 7
    print(sol.possibleStringCount(word, k))