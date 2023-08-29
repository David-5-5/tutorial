import math
class Solution:
    def preimageSizeFZF(self, k: int) -> int:
        co, i = 1/5, 2
        while (k * 5 >= 5 ** i):
            co += 1 / (5 ** i)
            i += 1
        
        begin = math.ceil(k / (co*5)) * 5
        result = 0
        while result < k:
            result = 0
            i = 1
            while (begin // (5 ** i) > 0):
                result += begin // (5 ** i)
                i += 1

            begin += 5

        return 0 if result > k else 5


if __name__ == "__main__":
    sol = Solution()
    k = 6
    print(sol.preimageSizeFZF(k))