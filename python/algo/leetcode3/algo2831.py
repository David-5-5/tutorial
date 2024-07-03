from typing import List
# 双指针
class Solution:
    def longestEqualSubarray(self, nums: List[int], k: int) -> int:
        m = max(nums)
        # group[i] 表示 i+1 在 nums 中[count, left, right] 
        g_inx = [[] for _ in range(m+1)]
        
        for i, num in enumerate(nums):
            g_inx[num].append(i)
    
        ans = 0
        for inx in g_inx:
            l = 0
            for r, p in enumerate(inx):
                while p-inx[l] - (r-l)>k:
                    l += 1
                ans = max(ans, r - l + 1)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,3,2,3,1,3], 3
    print(sol.longestEqualSubarray(nums, k))