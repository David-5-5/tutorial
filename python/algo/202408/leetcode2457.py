class Solution:
    def makeIntegerBeautiful(self, n: int, target: int) -> int:
        ns = str(n)
        ss = sum([int(i) for i in ns])
        ans, inx, inc = 0, len(ns) - 1, 0
        while ss > target:
            v = int(ns[inx]) + inc
            if v % 10:
                ss -= v - 1
                inc = 1
                ans += (10 - v) * (10 ** (len(ns)-1-inx))
            elif v == 10:
                ss -= 9
                inc = 1
            inx -= 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    n, target = 590, 1
    print(sol.makeIntegerBeautiful(n, target))
            
