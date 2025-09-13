from bisect import bisect_right
from cmath import inf
from typing import List


class Solution:
    def sumImbalanceNumbers(self, nums: List[int]) -> int:
        ans = 0
        n = len(nums)
        for left in range(n-1):
            sarr = [nums[left]]
            anb = 0
            for right in range(left+1, n):
                inx = bisect_right(sarr, nums[right])

                if (sarr[inx-1] + 1 if inx>0 else -inf) < nums[right] < (sarr[inx] - 1 if inx<len(sarr) else inf):
                    anb +=1 
                if 0 < inx < len(sarr) and  sarr[inx-1] + 1 == nums[right] == sarr[inx] - 1:
                    anb -= 1
                
                ans += anb
                if inx>0 or sarr[inx-1] != nums[right]:
                    sarr.insert(inx, nums[right])
        return ans

    def sumImbalanceNumbers2(self, nums: List[int]) -> int:
        # 复习，参考题解 时间复杂度 O(n^2)
        ans, n = 0, len(nums)
        vis = [-1] * (n + 2)
        for i, x in enumerate(nums):
            
            vis[x] = i
            cnt = 0
            for j in range(i + 1, n):
                y = nums[j]
                if vis[y] != i:
                    cnt += 1 - (vis[y - 1]==i) - (vis[y + 1]==i)
                    vis[y] = i
                ans += cnt
        
        return ans



if __name__ == "__main__":
    sol = Solution()
    print(sol.sumImbalanceNumbers([1,3,2]))