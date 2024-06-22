
from collections import Counter
from typing import List

class Solution:
    def countPairs(self, coordinates: List[List[int]], k: int) -> int:
        cnt = Counter()
        
        ans = 0
        for x, y in coordinates:
            for j in range(k+1):
                ans += cnt[x ^ j, y ^ (k-j)]
            cnt[x,y] += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    coordinates, k = [[1,2],[4,2],[1,3],[5,2]], 5
    coordinates, k = [[1,3],[1,3],[1,3],[1,3],[1,3]], 0
    print(sol.countPairs(coordinates, k))