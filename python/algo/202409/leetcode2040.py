from bisect import bisect_left, bisect_right
import math
from typing import List

# 2386题解中的题单：第 K 小/大
class Solution:
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:
        
        n2 = len(nums2)
        
        def check(mid:int) -> int:
            cnt = 0
            for v in nums1:
                if cnt > k: return cnt
                if v == 0:
                    if mid >=0: cnt += n2
                elif mid == 0:
                    cnt += bisect_right(nums2, 0) if v>0 else n2 - bisect_left(nums2, 0)
                else:
                    if (v*mid > 0 and mid< 0 ) or (v*mid<0 and mid > 0):
                        inx = bisect_left(nums2, math.ceil(mid/v))
                        cnt += n2-inx
                    else:
                        inx = bisect_right(nums2, mid//v)
                        cnt += inx
            return cnt

        left = min(nums1[0]*nums2[0], nums1[0]*nums2[-1],nums1[-1]*nums2[0],nums1[-1]*nums2[-1])
        right = max(nums1[0]*nums2[0], nums1[0]*nums2[-1],nums1[-1]*nums2[0],nums1[-1]*nums2[-1])

        # 当 left != 0 ，加上 left作为偏移
        return bisect_left(range(left, right), k, key=check) + left 

        # while left <= right:  # 区间不为空 采用闭区间二分
        #     # 循环不变量：
        #     # nums[left-1] < target
        #     # nums[right+1] >= target
        #     mid = (left + right) // 2
        #     if check(mid) < k:
        #         left = mid + 1  # 范围缩小到 [mid+1, right]
        #     else:
        #         right = mid - 1  # 范围缩小到 [left, mid-1]
        # return left

 
if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, k = [-4,-2,0,3], [2,4], 6
    # nums1, nums2, k = [-2,-1,0,1,2], [-3,-1,2,4,5], 3
    print(sol.kthSmallestProduct(nums1, nums2, k))