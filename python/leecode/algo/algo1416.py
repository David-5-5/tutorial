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

    # 空间的利用率完美
    def numberOfArrays2(self, s: str, k: int) -> int:
        n = len(s)
        kn = len(str(k))
        dp = [0 for _ in range(kn+1)]
        dpi = kn - 1
        dp[kn] = 1
        for i in range(n-1, -1, -1):
            dp[dpi] = 0
            for j in range(kn-1, -1, -1):
                if i + j < n:
                    if s[i] == '0':
                        break
                    if int(s[i:i+j+1]) <= k:
                        dp[dpi] += dp[(dpi+j+1) % (kn+1)]
            dp[dpi] = dp[dpi] % (10 ** 9 + 7)
            dpi = (dpi - 1) % (kn+1)

        return dp[(dpi+1) % (kn+1)] 



if __name__ == "__main__":
    sol = Solution()
    # s, k = "1317345345", 2000
    s, k = "000000000100", 2000
    
    print(sol.numberOfArrays(s, k))
    print(sol.numberOfArrays2(s, k))