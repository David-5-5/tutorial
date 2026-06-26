class Solution:
    def multiply(self, A: int, B: int) -> int:
        ans = 0
        for i in range(32):
            if (A >> i) & 1:
                ans += B << i
        return ans