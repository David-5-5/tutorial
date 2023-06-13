from functools import lru_cache

class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
        
        @lru_cache(maxsize = None)
        def inserts(l, r):
            if l >= r:
                return 0
            if r - l == 1 and s[r] == s[l]:
                return 0
            elif r - l == 1:
                return 1
            
            if s[l] == s[r]:
                return inserts(l+1, r-1)
            else:
                return 1 + min(inserts(l+1, r), inserts(l, r-1))
        
        return inserts(0, n-1)
    
if __name__ == "__main__":
    sol = Solution()
    s = "zzazz"
    print(sol.minInsertions(s))