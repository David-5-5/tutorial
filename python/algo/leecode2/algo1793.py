from typing import List
class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        # 从k为起点出发，向左右遍历到边界，并查找最大值
        # 当前节点为最小值，l，r初始设置为k，
        # 1、l，r分别向左右移动到大于等于最小值的数组下标。若l，r都小于当前最小值，
        # 2、首先移动到l,r中较大值的数组下标，并修改最小值
        # 重复上述步骤
        n = len(nums)
        minv, ans, l, r = nums[k], nums[k], k, k
        while l>0 or r<n-1:
            if l == 0:
                while r<n-1:
                    r += 1
                    minv = min(minv, nums[r])
                    ans = max(ans, minv*(r-l+1))
                continue
            if r == n-1:
                while l>0:
                    l -= 1
                    minv = min(minv, nums[l])
                    ans = max(ans, minv*(r-l+1))
                continue

            while r+1<=n-1 and nums[r+1]>=minv:
                r += 1
            ans = max(ans, (r-l+1)*minv)
            
            while l-1>=0 and nums[l-1]>=minv:
                l -= 1
            ans = max(ans, (r-l+1)*minv)

            if l == 0 or r == n -1 : continue

            if nums[r+1] == nums[l-1]:
                l, r = l-1, r+1
                minv = nums[r]
                ans = max(ans, minv*(r-l+1))
            elif nums[r+1] > nums[l-1]:
                r = r + 1
                minv = nums[r]
                ans = max(ans, minv*(r-l+1))
            else:
                l = l - 1
                minv = nums[l]
                ans = max(ans, minv*(r-l+1))

        return ans

    def maximumScore2(self, nums: List[int], k: int) -> int:
        # 简化上述代码,
        # 思路 从k为起点出发，向左右遍历到边界，并查找最大值
        # 当前节点为最小值，l，r初始设置为k，
        # 1、l，r分别向左右移动到大于等于最小值的数组下标。若l，r都小于当前最小值，
        # 2、首先移动到l,r中较大值的数组下标，并修改最小值
        # 重复上述步骤
        n = len(nums)
        minv, ans, l, r = nums[k], nums[k], k, k
        while l>0 or r<n-1:
            if r < n-1 and (l == 0 or nums[r+1] > nums[l-1]):
                r += 1
                minv = min(minv, nums[r])
            elif l>0 and (r == n-1 or nums[r+1] < nums[l-1]):
                l -= 1
                minv = min(minv, nums[l])
            else: # nums[r+1] == nums[l-1]
                r, l = r + 1, l- 1
                minv = min(minv, nums[r])

            ans = max(ans, minv*(r-l+1))

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,4,3,7,4,5], 3
    print(sol.maximumScore(nums, k))
    print(sol.maximumScore2(nums, k))    