class Solution:
    def minStickers(self, stickers, target: str) -> int:
        if len(stickers) == 0: return -1
        n = len(stickers)

        dp = [0 for _ in range(2 ^ n)]
        


        return dp[2^n -1]        
            
        
        
        


if __name__ == "__main__":
    sol = Solution()
    stickers = ["with","example","science"]
    target = "thehat"
    # import random
    # nums = [random.randint(1,20000) for _ in range(1234)]
    from datetime import datetime
    begin = datetime.now()
    print(sol.minStickers(stickers, target))
    print((datetime.now()- begin).total_seconds())
