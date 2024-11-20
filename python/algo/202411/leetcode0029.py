from bisect import bisect_left


INT_MX, INT_MN = 2**31-1, -2**31
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        # 特殊情况
        if dividend == INT_MN:
            if divisor == -1: return INT_MX # 不能溢出
        
        neg = False
        if dividend > 0 and divisor < 0 or dividend <0 and divisor > 0:
            neg = True

        if dividend < 0: dividend = -dividend
        if divisor < 0: divisor = -divisor

        # x * q < y False
        # x * q >= y True
        # q is quotient 商数
        def quickAdd(q:int) -> bool:
            x, y = divisor, dividend
            ans = 0
            while q:
                if q & 1:
                    ans += x
                    if y<ans:return False # 找更小值
                x += x
                q >>= 1
            if y<ans: return False
            else: return True # 找更大值
        
        left, right, ans = 1, INT_MX, 0
        while left <= right:
            # 注意溢出，并且不能使用除法
            mid = left + ((right - left) >> 1)
            check = quickAdd(mid)
            if check:
                ans = mid
                # 注意溢出
                if mid == INT_MX:
                    break
                left = mid + 1
            else:
                right = mid - 1

        return -ans if neg else ans
        

if __name__ == "__main__":
    sol = Solution()
    print(sol.divide(10, 3))