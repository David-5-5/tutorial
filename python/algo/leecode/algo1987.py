class Solution:
    def numberOfUniqueGoodSubsequences(self, binary: str) -> int:
        '''
        !!!!It's too hard to READ!!!!!!
        The official solution needs to be further understood
        '''
        mod = 10**9 + 7

        even = odd = 0
        for ch in binary:
            if ch == "0":
                even = (even + odd) % mod
            else:
                odd = (even + odd + 1) % mod
        
        ans = (even + odd + ("0" in binary)) % mod
        return ans