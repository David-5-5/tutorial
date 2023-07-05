import algo2376
class Solution:
    def numDupDigitsAtMostN(self, n: int) -> int:
        sol = algo2376.Solution()
        return n - sol.countSpecialNumbers(n)

if __name__ == "__main__":
    sol = Solution()
    print(sol.numDupDigitsAtMostN(1000))