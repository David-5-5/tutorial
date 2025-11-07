from typing import List

# 滑动窗口与双指针 - 双序列双指针 - 4.1 双指针
class Solution:
    def maxSum(self, nums1, nums2) -> int:
        sum1, sum2, inx1, inx2 = 0, 0, 0, 0
        n1, n2 = len(nums1), len(nums2)
        
        while inx1 < n1 or inx2 < n2:
            if inx1 < n1 and inx2 < n2:
                if nums1[inx1] < nums2[inx2]:
                    sum1 += nums1[inx1]
                    inx1 += 1
                elif nums1[inx1] > nums2[inx2]:
                    sum2 += nums2[inx2]
                    inx2 += 1
                else:
                    # equals
                    sum1 += nums1[inx1]
                    inx1 += 1
                    sum2 += nums2[inx2]
                    inx2 += 1
                    sum1 = max(sum1, sum2) % (10 ** 9 + 7)
                    sum2 = sum1
            elif inx1 < n1:
                while inx1 < n1:
                    sum1 += nums1[inx1]
                    inx1 += 1
            else:
                while inx2 < n2:
                    sum2 += nums2[inx2]
                    inx2 += 1
        return max(sum1, sum2) % (10 ** 9 + 7)

    def maxSum2(self, nums1: List[int], nums2: List[int]) -> int:
        # 复习，简化上述代码
        sum1 = sum2 = inx1 = inx2 = 0
        n1, n2 = len(nums1), len(nums2)
        
        while inx1 < n1 and inx2 < n2:
            if nums1[inx1] < nums2[inx2]:
                sum1 += nums1[inx1]
                inx1 += 1
            elif nums1[inx1] > nums2[inx2]:
                sum2 += nums2[inx2]
                inx2 += 1
            else:      # equals
                sum2 = sum1 = max(sum1, sum2) + nums1[inx1]
                inx1 += 1
                inx2 += 1
        for i in range(inx1, n1): sum1 += nums1[i]
        for i in range(inx2, n2): sum2 += nums2[i]

        return max(sum1, sum2) % (10 ** 9 + 7)    

if __name__ == "__main__":
    sol = Solution()
    nums1 = [2,4,5,8,10]
    nums2 = [4,6,8,9]
    print(sol.maxSum(nums1, nums2))