from bisect import bisect_left
import heapq
from typing import List

# 周赛 307
class Solution:
    def kSum(self, nums: List[int], k: int) -> int:
        # 参考题解，方法一：最小堆
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

    def kSum2(self, nums: List[int], k: int) -> int:
        # 参考题解，方法二：二分
        total= 0
        for i, v in enumerate(nums):
            if nums[i]>=0: total += v
            else: nums[i] = -v
        
        nums.sort()
        
        # 理解上有些难度
        def check(limit: int) ->bool:
            cnt = 1 # 空序列
            def dfs(i:int, s:int):
                nonlocal cnt
                if i == len(nums) or cnt == k or s + nums[i] > limit:
                    return
                cnt += 1
                dfs(i+1, s) # 不选
                dfs(i+1, s + nums[i]) # 选
            dfs(0, 0)
            return cnt == k

        return total - bisect_left(range(sum(nums)), True, key=check)

if __name__ == "__main__":
    sol = Solution()    
    nums, k = [2,4,-2], 5
    print(sol.kSum(nums, k))

    nums, k = [2,4,-2], 5 # 在算法在原数组上修改，重新赋值
    print(sol.kSum2(nums, k))