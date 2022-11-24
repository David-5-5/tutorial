class Solution:
    def minStickers(self, stickers, target: str) -> int:
        if len(stickers) == 0: return -1
        n = len(stickers)

        alphaDict = {}
        inx = 0
        for letter in target:
            if letter not in alphaDict:
                alphaDict[letter] = inx
                inx += 1
        
        matrix = [[0 for _ in range(len(alphaDict))] for _ in range(n + 1)]
        
                
            
        
        
        


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
