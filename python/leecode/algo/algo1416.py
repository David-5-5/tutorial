from functools import lru_cache
class Solution:
    def numberOfArrays(self, s: str, k: int) -> int:
        n = len(s)
        @lru_cache(maxsize = 10 ** 2)
        def nums(begin) :
            if begin == n: return 1
            if s[begin] == '0':
                return 0
            ret = 0
            for i in range(1, min(n-begin, len(str(k)))+1):
                if int(s[begin:begin + i]) <= k:
                    ret += nums(begin+i)
            return ret

        return nums(0) % (10 ** 9 + 7)


if __name__ == "__main__":
    sol = Solution()
    s, k = "1317", 2000
    print(sol.numberOfArrays(s, k))