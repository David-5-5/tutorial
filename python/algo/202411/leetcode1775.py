from typing import List

# 贪心专题
class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        nums1.sort()
        nums2.sort()
        sum1, sum2 = sum(nums1), sum(nums2)

        # sum(nums1) < sum(nums2)
        if sum1 > sum2:
            nums1, nums2 = nums2, nums1
        
        ans, diff, i, j, n = 0, abs(sum2 - sum1), 0, len(nums2) - 1, len(nums1)
        
        while diff and (i < n or j >=0):
            if i < n and j >= 0:
                if 6 - nums1[i] > nums2[j] - 1:
                    diff -= min(diff, 6 - nums1[i])
                    i += 1
                else:
                    diff -= min(diff, nums2[j] - 1)
                    j -= 1
            elif i < n:
                diff -= min(diff, 6 - nums1[i])
                i += 1
            elif j >= 0:
                diff -= min(diff, nums2[j] - 1)
                j -= 1
            else: break

            ans += 1
        return -1 if diff else ans

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [6,6], [1]
    print(sol.minOperations(nums1, nums2))