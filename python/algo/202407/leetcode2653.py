from bisect import bisect_left
from typing import List

# 由于值域为 [-50, 50], 计数排序 + 滑动窗口，时间复杂度为 O(50 *n)
# 排序 + 滑动窗口，时间复杂度为 O(nlogn) ？
class Solution:
    def getSubarrayBeauty(self, nums: List[int], k: int, x: int) -> List[int]:
        n = len(nums)

        ans = [0] * (n-k+1)

        win = nums[:k-1]
        win.sort()
        for i, (in_, out) in enumerate(zip(nums[k-1:], nums)):
            inx = bisect_left(win, in_)
            win.insert(inx, in_)
            if win[x-1] < 0:
                ans[i] = win[x-1]
            outx = bisect_left(win, out)
            win.pop(outx)
        return ans

    def getSubarrayBeauty2(self, nums: List[int], k: int, x: int) -> List[int]:
        # 滑动窗口 + 计数排序 ，还是这个方法快
        n = len(nums)

        ans = [0] * (n-k+1)

        cnt = [0] * 101
        for v in nums[:k-1]:
            cnt[v+50] += 1

        for i, (in_, out) in enumerate(zip(nums[k-1:], nums)):
            cnt[in_+50] += 1
            
            left = x
            for j in range(50):
                left -= cnt[j]
                if left <= 0 :
                    ans[i] = j - 50
                    break
                
            cnt[out+50] -= 1
        return ans    

if __name__ == "__main__":
    sol = Solution()
    nums, k, x = [-1,-2,-3,-4,-5], 2, 2
    print(sol.getSubarrayBeauty(nums, k, x))   
    print(sol.getSubarrayBeauty2(nums, k, x))    