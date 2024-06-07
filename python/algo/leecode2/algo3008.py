from typing import List
class Solution:
    def beautifulIndices(self, s: str, a: str, b: str, k: int) -> List[int]:
        
        # Python program for KMP Algorithm
        def KMPSearch(pat, txt):
            M = len(pat)
            N = len(txt)
        
            # create lps[] that will hold the longest prefix suffix
            # values for pattern
            lps = [0]*M
            j = 0 # index for pat[]
            match = []
            # Preprocess the pattern (calculate lps[] array)
            computeLPSArray(pat, M, lps)
        
            i = 0 # index for txt[]
            while (N - i) >= (M - j):
                if pat[j] == txt[i]:
                    i += 1
                    j += 1
        
                if j == M:
                    # print ("Found pattern at index " + str(i-j))
                    match.append(i-j)
                    j = lps[j-1]
        
                # mismatch after j matches
                elif i < N and pat[j] != txt[i]:
                    # Do not match lps[0..lps[j-1]] characters,
                    # they will match anyway
                    if j != 0:
                        j = lps[j-1]
                    else:
                        i += 1

            return match
        def computeLPSArray(pat, M, lps):
            len = 0 # length of the previous longest prefix suffix
        
            lps[0] # lps[0] is always 0
            i = 1
        
            # the loop calculates lps[i] for i = 1 to M-1
            while i < M:
                if pat[i]== pat[len]:
                    len += 1
                    lps[i] = len
                    i += 1
                else:
                    # This is tricky. Consider the example.
                    # AAACAAAA and i = 7. The idea is similar
                    # to search step.
                    if len != 0:
                        len = lps[len-1]
        
                        # Also, note that we do not increment i here
                    else:
                        lps[i] = 0
                        i += 1        
        
        from bisect import bisect_right
        ans = []
        amtach = KMPSearch(a, s)
        bmtach = KMPSearch(b, s)
        if not bmtach:
            return ans
        for pos in amtach:
            inx = bisect_right(bmtach, pos+k)
            if inx and bmtach[inx-1]>=pos-k:
                ans.append(pos)

        return ans
    

if __name__ == "__main__":
    sol = Solution()
    s, a, b, k = "isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15
    s, a, b, k = "wfvxfzut", "wfv", "ut", 6
    print(sol.beautifulIndices(s, a, b, k))