from bisect import bisect_right
from cmath import inf
from typing import List

pals = set()
pals.add(1)
def reverse(val: int) -> int:
    res = 0
    while val != 0:
        res = (res << 1) | (val & 1)
        val >>= 1
    return res

left = 1
while True:
    shift = left.bit_length()
    right = reverse(left)
    val = left << shift | right

    if val > 5000: break
    pals.add(val)
    
    if left << (shift+1) | right < 5001 :
        pals.add(left << (shift+1) | right)
    if left << (shift+1) | 1<< shift | right < 5001:
        pals.add(left << (shift+1) | 1<< shift | right)

    left += 1

pals = list(pals)
pals.sort()

class Solution:
    def minOperations(self, nums: List[int]) -> List[int]:
        n = len(nums)
        
        ans = [inf] * n
        for i in range(n):
            idx = bisect_right(pals, nums[i])
            if idx: ans[i] = min(ans[i], nums[i]-pals[idx-1])
            if idx < len(pals): ans[i] = min(ans[i], pals[idx]-nums[i])
        
        return ans


if __name__ == "__main":
    Solution().minOperations([6,7,12])