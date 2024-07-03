from typing import List
class Solution:
    def carPooling(self, trips: List[List[int]], capacity: int) -> bool:
        maxl = 0
        n = len(trips)
        for i in range(n):
            maxl = max(maxl, trips[i][1],trips[i][2])
        
        da = [0] * maxl
        for i in range(n):
            da[trips[i][1]] += trips[i][0]
            if trips[i][2] < maxl:
                da[trips[i][2]] -= trips[i][0]

        sumc = 0
        for i in range(maxl):
            sumc += da[i]
            if sumc > capacity:
                return False

        return True

if __name__ == "__main__":
    sol = Solution()
    trips, capacity = [[2,1,5],[3,5,7]],3
    print(sol.carPooling(trips, capacity))