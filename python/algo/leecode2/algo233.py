class Solution:
    def countDigitOne(self, n: int) -> int:
        # 计算小于n的每位出现1的次数，假定n由 digits[0..len_n-1]
        # digits[i], 第i位出现1的次数，包括两部分：
        # 1）当digits[i]的前缀为0 .. int(digits[0..i-1])-1，即小于int(digits[0..i-1])时
        #    出现的次数为 int(digits[0..i-1]) * (10 ^ len(digits[i+1..n-1]))
        # 2) 当digits[i]的前缀为int(digits[0..i-1])，若
        #   2.1） digits[i] == 1 时，次数为 int(digits[i+1..n-1])
        #   2.2） digits[i] > 1 时，次数为  (10 ^ len(digits[i+1..n-1]))
        #   2.3） digits[i] == 0 时，次数为 0

        strn = str(n)

        lenn = len(strn)

        def toint(begin: int, end:int):
            if begin >= end:
                return 0
            else:
                return int(strn[begin:end])
        cnt = 0
        for i in range(lenn):
            prec = toint(0,i) + 1
            subc = toint(i+1, lenn) + 1
            cnt += (prec - 1) * (10 ** (lenn-i-1))
            if int(strn[i]) == 1:
                cnt += subc
            elif int(strn[i]) > 1:
                cnt += (10 ** (lenn-i-1))
        return cnt
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.countDigitOne(0))