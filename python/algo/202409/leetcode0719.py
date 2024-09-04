from bisect import bisect_left
import heapq
from typing import List

# 2386题解中的题单：第 K 小/大
class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        # 最小堆 排序后构造，初始化i + 1 = j 两两差，不断增加 j
        # k = n*(n-1)/2 !!!OVERTIME!!!!
        n  = len(nums)
        nums.sort()
        q = []
        for i in range(1, n):
            q.append((nums[i]-nums[i-1],i-1,i))
        
        heapq.heapify(q)
        while k>1:
            k -= 1
            _, i, j = heapq.heappop(q)
            if j+1<n:heapq.heappush(q, (nums[j+1]-nums[i],i,j+1))
        
        return q[0][0]

    def smallestDistancePair2(self, nums: List[int], k: int) -> int:
        # 方法一不行，
        # 方法二：二分
        # 理解上有些难度
        nums.sort()

        def count(mid) -> int:
            cnt = 0
            for j, v in enumerate(nums):
                i = bisect_left(nums, v-mid, 0, j)
                cnt += j-i
            
            return cnt

        return bisect_left(range(nums[-1]-nums[0]), k, key=count)


if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,3,1], 1
    nums, k = [9,10,7,10,6,1,5,4,9,8], 18
    print(sol.smallestDistancePair(nums, k))
    print(sol.smallestDistancePair2(nums, k))