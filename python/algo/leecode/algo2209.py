from functools import lru_cache


class Solution:
    '''
    Pass with Poor spatial complexity 
    '''
    def minimumWhiteTiles(self, floor: str, numCarpets: int, carpetLen: int) -> int:
        n = len(floor)        
        whites = [0] * n
        
        for i in range(n):
            whites[i] = int(floor[i]) + (whites[i-1] if i else 0)
        
        if whites[i] <= numCarpets: return 0
        
        @lru_cache(maxsize = None)
        def whiteTiles(cur, leftCarpets) -> int:
            if cur <= carpetLen * leftCarpets: return 0
            if leftCarpets == 0: return whites[cur-1]
            minT = whiteTiles(cur-carpetLen, leftCarpets-1)
            return min(minT, whiteTiles(cur-1, leftCarpets) + int(floor[cur-1]))
        
        return whiteTiles(n, numCarpets)

if __name__ == "__main__":
    sol = Solution()
    floor = "10110101"
    numCarpets = 2
    carpetLen = 2
    print(sol.minimumWhiteTiles(floor, numCarpets, carpetLen))