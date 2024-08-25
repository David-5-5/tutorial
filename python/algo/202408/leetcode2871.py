from typing import List

# 双周赛 114
# AND　运算的特征
#   AND 运算的数越多，结果越小
class Solution:
    # 参考题解
    def maxSubarrays(self, nums: List[int]) -> int:
        ans, a = 0, -1 # -1 的位全为 1
        for x in nums:
            a &= x
            if a == 0: # AND 结果大于 0，则分组的值会越大
                ans += 1
                a = -1
        return max(ans, 1)
if __name__ == "__main__":
    sol = Solution()    
    # nums = [1,0,2,0,1,2]
    nums = [1,1,1,1,1,1]
    print(sol.maxSubarrays(nums))
    