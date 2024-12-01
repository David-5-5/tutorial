class Solution:
    def smallestNumber(self, n: int) -> int:
        l = len(bin(n)) - 2
        ans = 0
        for i in range(l):
            ans |= 1 << i
        return ans

if __name__ == "__main__":
    sol = Solution()