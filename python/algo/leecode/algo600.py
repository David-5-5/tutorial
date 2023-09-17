class Solution:
    def findIntegers(self, n: int) -> int:
        bit = len(bin(n)) - 2

        # The count of Consecutive 1
        # dp[0] = 0, non-exist
        # dp[1] = 0, non-exist
        # dp[2] = 2 ** k / 4 + dp[0] + dp[1]
        # dp[k] = 2 ** k / 4 + dp[k-2] + dp[k-1]
        # 说明dp[k],表明从0～2**k-1，共2**k数存在连续11的数量，分两部分
        # 高位2**(k-1)个包含2 ** k / 4 + dp[k-2],
        #    因为最高为1，第二为1，即2 ** k / 4
        #    第二位为0，后面的数量等于dp[k-2]
        # 低位2**(k-1)的数量即为dp[k-1]
        # dp从低位计算到高位，代码如下：
        # 举例说明k=4
        # 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        #       -     - -        -  -  -  -  -
        # {dp1}
        # { dp2 }
        # |    part3    | | part2 | | part1  |
        # {    dp[3]    } { dp[2] } {   16/4 }
        # {   ~~~~~~   dp[4]   ~~~~~       }
        dp = [0 for _ in range(bit+1)]
        for i in range(2, bit+1):
            dp[i] = 2 ** (i-2) + dp[i-2] + dp[i-1]

        
        def cnt(num):
            '''
            计算num以下, 包含连续11的数量
            '''
            c_bit = len(bin(num)) - 2

            if num < 3:
                return 0

            if num & (2 ** (c_bit-2)) == 2 ** (c_bit-2):
                # 第二位为1，part1的部分，以及part2、part3的全部
                # 由于part1是连续的，因此减去:
                #     2 ** (c_bit)-1 和 num的差即可
                return dp[c_bit] - (2 ** (c_bit)-1 - num)
            else:
                # 若第二为0，不包含part1，包含part2的部分及part3全部
                # cnt(num- 2 ** (c_bit-1))递归计算part2
                # dp[c_bit-1]为第三部分
                return dp[c_bit-1] + cnt(num- 2 ** (c_bit-1))
        
        return n - cnt(n) + 1

if __name__ == "__main__":
    sol = Solution()
    print(sol.findIntegers(18))    