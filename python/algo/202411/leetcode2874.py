from typing import List

# 周赛 365
class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        # 参考题解 前后缀分解 前缀最大值 + 后缀最大值 遍历 j
        n = len(nums)
        suf_max, per_max = [0] * n, [0] * n

        suf_max[-1] = nums[-1]
        for i in range(n-2, -1, -1):
            suf_max[i] = max(suf_max[i+1], nums[i])
        
        per_max[0] = nums[0]
        for i in range(1, n):
            per_max[i] = max(per_max[i-1], nums[i])
        
        ans = 0
        # 遍历 j
        for i in range(1, n-1):
            ans = max(ans, (per_max[i-1]-nums[i])*suf_max[i+1])
        
        return ans

    def maximumTripletValue2(self, nums: List[int]) -> int:
        # 参考题解 max(nums[i]-nums[j])，遍历 k
        n = len(nums)
        pre_max ,m_diff = nums[0], nums[0] - nums[1]
        
        ans = 0
        # 遍历 k
        for k in range(2, n):
            ans = max(ans, m_diff*nums[k])
            if nums[k-1] > pre_max: pre_max = nums[k-1]
            if pre_max - nums[k] > m_diff: m_diff = pre_max - nums[k]
        
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums = [12,6,1,2,7]
    print(sol.maximumTripletValue(nums))
