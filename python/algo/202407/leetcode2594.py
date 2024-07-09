from bisect import bisect_left
from math import floor, sqrt
from typing import List


class Solution:
    def repairCars(self, ranks: List[int], cars: int) -> int:
        
        def repair(m:int) -> int:
            res = 0
            for v in ranks:
                res += floor(sqrt(m / v))
            return res
    
        return bisect_left(range(min(ranks)*cars*cars), cars, key=repair)

if __name__ == "__main__":
    sol = Solution()
    ranks, cars = [1,2,3,4], 4
    print(sol.repairCars(ranks, cars))
