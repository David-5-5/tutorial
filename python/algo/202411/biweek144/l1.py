class Solution:
    def canAliceWin(self, n: int) -> bool:
        rem, i = 10, 0
        while n >= rem:
            n -= rem
            i = 1 - i
            rem -= 1
        if i == 0: return False
        else: return True
        
if __name__ == "__main__":
    sol = Solution()
