from typing import List
class Solution:
    def beautifulIndices(self, s: str, a: str, b: str, k: int) -> List[int]:
        ans = []
        n = len(s)

        i = s.find(a, 0)
        j = -1
        while i != -1:
            if (i-k if i>k else 0) <= j <= i+k:
                ans.append(i)
            else:
                j = s.find(b, i-k if i>k else 0, min(n,i+k+len(b)))
                if j != -1:
                    ans.append(i)
            
            i = s.find(a, i+1)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    s, a, b, k = "isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15
    s, a, b, k = "uzqauzqw", "uzq", "psnso", 2
    print(sol.beautifulIndices(s, a, b, k))