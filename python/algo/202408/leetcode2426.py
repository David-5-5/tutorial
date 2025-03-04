from bisect import bisect_left, bisect_right
from typing import List

# nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff     (1)
# nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff     (2)
# 令 a[i] = nums1[i] - nums2[i], 则 (2) 为 
# a[i] <= a[j] + diff
# 转化为求逆序对

# 树状数组
class BIT:
    # 数组从零开始
    def __init__ (self, n:int) -> None:
        self.nums = [0] * n

    def add(self, i:int, val :int):
        while i < len(self.nums):
            self.nums[i] += val
            i += i & -i

    def query(self, i:int) ->int:
        res = 0
        while i > 0:
            res += self.nums[i]
            i -= i & -i
        return res

class Solution:
    # 方法一: 树状数组
    def numberOfPairs(self, nums1: List[int], nums2: List[int], diff: int) -> int:
        a = [x-y for x, y in zip(nums1, nums2)]
        b = a.copy() # 离散化，将数值对应到下标
        b.sort()

        t = BIT(len(b)+1)
        ans = 0
        for x in a:
            i = bisect_right(b, x+diff)
            ans += t.query(i)

            t.add(bisect_left(b, x)+1, 1)
        
        return ans

    # 方法二: 合并排序
    def numberOfPairs2(self, nums1: List[int], nums2: List[int], diff: int) -> int:
        a = [x-y for x, y in zip(nums1, nums2)]

        def mergeSort(nums: List[int]) -> int:
            if len(nums) <= 1:
                return 0

            mid = len(nums) // 2
            l = nums[:mid]
            r = nums[mid:]
            cnt = mergeSort(l) + mergeSort(r)
            i = 0
            for x in r:
                while i < len(l) and l[i] <= x + diff:
                    i += 1
                cnt += i
                
            inx1 = inx2 = inx = 0
            while True:
                if inx1 == len(l):
                    nums[inx:] = r[inx2:]
                    break
                if inx2 == len(r):
                    nums[inx:] = l[inx1:]
                    break
                if l[inx1] <= r[inx2]:
                    nums[inx] = l[inx1]
                    inx += 1
                    inx1 += 1
                else:
                    nums[inx] = r[inx2]
                    inx += 1
                    inx2 += 1
            return cnt

        return mergeSort(a)

    
if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, diff = [3,2,5], [2,2,1], 1
    print(sol.numberOfPairs(nums1, nums2, diff))
    print(sol.numberOfPairs2(nums1, nums2, diff))    