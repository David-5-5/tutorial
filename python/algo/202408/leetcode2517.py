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
        #         right = mid
        #     else:
        #         left = mid
        # return right    

    def maximumTastiness2(self, price: List[int], k: int) -> int:
        # 进一步理解 Left：true, right：False
        # 目标 k/target 越大, 取值 mid 越小
        price.sort()
        right = price[-1] - price[0]
        
        def check(step: int) -> int:
            inx, cnt = 0, 0
            while inx < len(price):
                cnt += 1
                inx = bisect_left(price, price[inx] + step)
            
            return cnt
            
        left, right = -1, price[-1] - price[0] + 1  # 开区间 (left, right)
        while left + 1 < right:  # 区间不为空
            mid = (left + right) // 2
            # 循环不变量：
            # nums[left] < target
            # nums[right] >= target
            if check(mid) < k:
                right = mid  # left = mid 范围缩小到 (left, mid)
            else:
                left = mid  # right = mid 范围缩小到 (mid, right)
        return left # right



if __name__ == "__main__":
    sol = Solution()
    price, k = [13,5,1,8,21,2], 3
    print(sol.maximumTastiness(price, k))
    print(sol.maximumTastiness2(price, k))