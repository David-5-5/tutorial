import bisect
class Solution:
    def minimumOneBitOperations(self, n: int) -> int:
        '''Study Grey code 格雷码
        '''
        if n == 0:
            return 0
        x = len(bin(n)) - 3
        return (1 << (x + 1)) - 1 - self.minimumOneBitOperations(n - (1 << x))

    def minimumOneBitOperations2(self, n: int) -> int:
        '''Study Grey code to binary
        '''
        bits = len(bin(n)) - 2
        bins = 0
        hi = 0
        for i in range(bits-1, -1, -1):
            gi = n >> i
            if i == bits-1:
                bi = gi
            else:
                bi = hi ^ gi
            hi = bi
            bins |= bi << i
        return bins

if __name__ == "__main__":
    sol = Solution()
    '''
    oct     bin     grey
    0       0000    0000
    1       0001    0001   
    2       0010    0011
    3       0011    0010
    4       0100    0110
    5       0101    0111
    6       0110    0101
    7       0111    0100
    8       1000    1100
    '''
    print(sol.minimumOneBitOperations(100))
    print(sol.minimumOneBitOperations2(100))


