from typing import List
import collections

class Solution:
    def maxGroupNumber(self, tiles: List[int]) -> int:
        m = collections.Counter(tiles)
        dp = {(0, 0): 0}
        for num in sorted(m):
            ndp=collections.defaultdict(int)
            x,y,z=m[num],m[num+1],m[num+2]
            for (i,j),c in dp.items():
                for k in range(3):
                    if i+k<=x and j+k<=y and k<=z:
                        ndp[j+k,k]=max(ndp[j+k,k],c+(x-i-k)//3+k)
            dp=ndp
        return max(dp.values())

if __name__ == "__main__":
    sol = Solution()
    tiles = [2,2,2,3,4]
    print(sol.maxGroupNumber(tiles))