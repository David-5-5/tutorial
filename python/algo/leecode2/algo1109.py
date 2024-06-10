from typing import List
from itertools import accumulate
class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        da = [0] * n

        for f,l,s in bookings:
            da[f-1] += s
            if l < n:
                da[l] -= s 
        
        return list(accumulate(da))

if __name__ == "__main__":
    sol = Solution()
    bookings, n = [[1,2,10],[2,3,20],[2,5,25]], 5