from functools import cache
from typing import List

# 周赛 353
class Solution:
    def maxNonDecreasingLength(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答，记忆化搜索 + 贪婪
        n = len(nums1)
        pair = [nums1, nums2]
        ans = 1
        @cache
        def dfs(i:int, k:int) -> int:
            nonlocal ans # ans 在 max() 函数中不生效
            if i == n: return 0

            if min(nums1[i], nums2[i]) >= pair[k][i-1]: # 尽量取最小值，减少递归分支
                return 1 + dfs(i+1, 1 if nums1[i]>=nums2[i] else 0)
            elif min(nums1[i], nums2[i]) < pair[k][i-1] and max(nums1[i], nums2[i]) >=pair[k][i-1]:
                res = 1 + dfs(i+1, 1 if nums1[i]>nums2[i] else 0)
                if res > ans: ans = res
                return 1 + dfs(i+1, 0 if nums1[i]>nums2[i] else 1)
            else: # max(nums1[i], nums2[i]) < pair[k][i-1]
                res = 1 + dfs(i+1, 1 if nums1[i]>=nums2[i] else 0)
                if res > ans: ans = res
                return 0

        res = 1 + dfs(1, 1 if nums1[0]>=nums2[0] else 0)
        
        return max(ans,res)

    def maxNonDecreasingLength2(self, nums1: List[int], nums2: List[int]) -> int:
        # 参考题解，代码更加简洁，但未剪枝
        n = len(nums1)
        pair = (nums1, nums2)

        @cache
        def dfs(i:int, k:int) -> int:
            if i == n-1: return 1

            res = 1
            if pair[k][i] <= nums1[i+1]:
                res = dfs(i+1, 0) + 1
            if pair[k][i] <= nums2[i+1]:
                res = max(res, dfs(i+1,1)+1)
            return res
        return max(dfs(i,k) for k in range(2) for i in range(n-1, -1, -1))

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [1,3,2,1], [2,2,3,4]
    nums1, nums2 = [17,11,6,2,17], [18,9,7,17,5]
    print(sol.maxNonDecreasingLength(nums1, nums2))
    print(sol.maxNonDecreasingLength2(nums1, nums2))