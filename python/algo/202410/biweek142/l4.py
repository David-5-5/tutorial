class Solution:
    def possibleStringCount(self, word: str, k: int) -> int:
        if len(word) == k: return 1

        ans = 0
        MOD = 10 ** 9 + 7

        word = word + '0'
        count = 1
        nums = []
        for i in range(1, len(word)):
            if word[i-1] == word[i]:
                count += 1
            else:
                nums.append(count)
                count = 1

        f = [0] * k
        f[0] = 1
        for i in range(len(nums)):
            for j in range(1, min(k, nums[i])+1):
                f[k-1] += f[k-j]
        
        ans = pow(2, len(nums), MOD)
        return (ans - 2 * sum(f)) % MOD

if __name__ == "__main__":
    sol = Solution()