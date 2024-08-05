from bisect import bisect_left
from typing import List


class Solution:
    def maximumTastiness(self, price: List[int], k: int) -> int:
        price.sort()
        right = price[-1] - price[0]
        

        def check(step: int) -> bool: 
            step += 1 # Left true, right False
            begin, cnt = price[0], 1
            while cnt < k:
                inx = bisect_left(price, begin + step)
                if inx == len(price):return True
                begin, cnt = price[inx], cnt + 1
            
            return False
            
        return bisect_left(range(right), True, key=check)
        # left = -1
        # right = price[-1] - price[0] + 1
        # while left + 1 < right:
        #     mid = (left + right) // 2
        #     if check(mid):
        #         left = mid
        #     else:
        #         right = mid
        # return right    

if __name__ == "__main__":
    sol = Solution()
    price, k = [13,5,1,8,21,2], 3
    print(sol.maximumTastiness(price, k))