import collections
from typing import List

class Solution:
    def countPairs(self, coordinates: List[List[int]], k: int) -> int:
        n = len(coordinates)
        m = 10 ** 6 + 1
        group = collections.defaultdict(int)
        for pos in coordinates:
            group[pos[0]*m+pos[1]] += 1
        
        ans = 0
        for i in range(n-1):
            x, y = coordinates[i][0], coordinates[i][1]
            group[x*m+y] -= 1 

            for j in range(k+1):
                x_ = x ^ j
                y_ = y ^ (k-j)
                ans += group[x_*m+y_]
        return ans

if __name__ == "__main__":
    sol = Solution()
    coordinates, k = [[1,2],[4,2],[1,3],[5,2]], 5
    coordinates, k = [[1,3],[1,3],[1,3],[1,3],[1,3]], 0
    print(sol.countPairs(coordinates, k))