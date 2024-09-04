import heapq
from typing import List

# 周赛 307
class Solution:
    def kSum(self, nums: List[int], k: int) -> int:
        # 参考题解
        total= 0
        for i, v in enumerate(nums):
            if nums[i]>=0: total += v
            else: nums[i] = -v
        
        nums.sort()
        # 关键点：构造nums中前 k 个最小值和
        q = [(0,0)]
        while k>1:
            k -= 1
            p_sum, i = heapq.heappop(q)
            if i == len(nums):continue
            heapq.heappush(q, (p_sum+nums[i], i+1))
            if i: heapq.heappush(q, (p_sum+nums[i]-nums[i-1], i+1))
        return total - q[0][0]

if __name__ == "__main__":
    sol = Solution()    
    nums, k = [2,4,-2], 5
    print(sol.kSum(nums, k))