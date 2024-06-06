class Solution:
    def findMaximumNumber(self, k: int, x: int) -> int:
        def countDigitOne(n: int) -> int:
            strn = bin(n)[2:]

            lenn = len(strn)

            def toint(begin: int, end:int):
                if begin >= end:
                    return 0
                else:
                    return int(strn[begin:end],2)
            cnt = 0
            for i in range(lenn):
                if (lenn-i) % x !=0: continue
                prec = toint(0,i) + 1
                subc = toint(i+1, lenn) + 1
                cnt += (prec - 1) * (2 ** (lenn-i-1))
                if int(strn[i]) == 1:
                    cnt += subc
                elif int(strn[i]) > 1:
                    cnt += (2 ** (lenn-i-1))
            return cnt
        
        # 高级写法，替代下面的二分查找
        from bisect import bisect_left
        return bisect_left(range((k + 1) << x), k + 1, key=countDigitOne) - 1
        
        # left = 0
        # right = (k+1) << x
        # while left + 1 < right:
        #     mid = (left + right) // 2
        #     if countDigitOne(mid) > k:
        #         right = mid
        #     else:
        #         left = mid
        # return left

if __name__ == "__main__":
    sol = Solution()
    print(sol.findMaximumNumber(9,1))