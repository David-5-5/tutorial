from bisect import bisect_right


N = 10 ** 9
fib = [1,1]
while fib[-1] < N:
    fib.append(fib[-1]+fib[-2])

class Solution:
    def findMinFibonacciNumbers(self, k: int) -> int:
        ans = 0
        while k:
            inx = bisect_right(fib, k)
            ans += 1
            k -= fib[inx-1]

        return ans    
        