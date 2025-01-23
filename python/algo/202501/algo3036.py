from typing import List

def kmp(s:str, p:str) -> int:
    m, n = len(s), len(p)
    p_pi = [0] * n

    ans = 0

    # Compute the prefix function of p
    for i in range(1, n):
        j = p_pi[i-1]
        while j>0 and p[j] != p[i]: j = p_pi[j-1]
        if p[j] == p[i]:
            p_pi[i] = j+1
        else:
            p_pi[i] = j
    
    j = 0 # j 既是 pattern 索引，也是 s[i] 的 pi 值 
    for i in range(m):
        while j>0 and p[j] != s[i]: j = p_pi[j-1]
        if p[j] == s[i]:
            j += 1

        # Find match
        if j == n:
            ans += 1
            j = p_pi[j-1] 
    
    return ans
class Solution:
 
    def countMatchingSubarrays(self, nums: List[int], pattern: List[int]) -> int:
        pat_str = ""
        for v in pattern:
            if v == 1: pat_str += "a"
            elif v == 0: pat_str += "b"
            else: pat_str += "c"
        
        tomatch = ""
        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]: tomatch += "a"
            elif nums[i] == nums[i-1]: tomatch += "b"
            else: tomatch += "c"
        
        return kmp(tomatch, pat_str)