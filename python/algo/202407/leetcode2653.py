from bisect import bisect_left
from typing import List

# 树状数组模板
class FenwickTree:
    def __init__(self, n):
        self.tree = [0] * (n + 1)

    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i

    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res

    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)


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

    def getSubarrayBeauty3(self, nums: List[int], k: int, x: int) -> List[int]:
        # 2025.7 复习 数状数组 二分查找
        n = len(nums)
        ans = [0] * (n-k+1)
        ft = FenwickTree(101)
        
        
        def getXth() -> int:
            # 二分查找
            l, r = 1, 101
            while l < r:
                mid = (l+r)//2
                if mid > 51: return 0   # 剪枝
                if ft.query(1, mid) >= x:
                    r = mid
                else:
                    l = mid + 1
            return l - 51

        for v in nums[:k-1]:
            ft.update(v+51, 1)

        for i, v in enumerate(nums[k-1:]):
            ft.update(v+51, 1)
            ans[i] = getXth()
            ft.update(nums[i]+51, -1)

        return ans
        


if __name__ == "__main__":
    sol = Solution()
    nums, k, x = [-1,-2,-3,-4,-5], 2, 2
    print(sol.getSubarrayBeauty(nums, k, x))   
    print(sol.getSubarrayBeauty3(nums, k, x))    