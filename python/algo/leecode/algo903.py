from functools import lru_cache
class Solution:
    def numPermsDISequence(self, s: str) -> int:
        ''' Offical soluton 1
        '''
        MOD = 10**9 + 7
        n = len(s)
        
        @lru_cache(maxsize = None)
        def dp(i:int, j:int):
            if i == 0: return 1
            elif s[i-1] == 'D':
                return sum(dp(i-1,k) for k in range(j, i)) % MOD
            else:
                return sum(dp(i-1,k) for k in range(i)) % MOD

        return sum(dp(n, j) for j in range(n+1)) % MOD

    def numPermsDISequence2(self, s: str) -> int:
        ''' Offical soluton 2
        And the third party:
        https://leetcode.cn/problems/valid-permutations-for-di-sequence/solutions/
        669040/dong-tai-gui-hua-tong-su-yi-dong-de-zhua-4c92/
        '''        

        MOD = 10**9 + 7
        n = len(s)
        
        @lru_cache(maxsize = None)
        def dp(i:int, j:int):
            if not(0 <= j <= i):
                return 0            
            if i == 0: return 1
            elif s[i-1] == 'D':
                return dp(i,j+1) + dp(i-1,j)
            else:
                return dp(i,j-1) + dp(i-1,j-1)

        return sum(dp(n, j) for j in range(n+1)) % MOD



if __name__ == "__main__":
    sol = Solution()
    s = "DIDI"
    print(sol.numPermsDISequence(s))