from typing import List
from sortedcontainers import SortedList
class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        '''prefix sum & binary search
        '''
        n = len(nums)
        # The peformance is improved by using SortedList replace of 
        # list with bisect function
        sort_pres = SortedList()
        presum = ans = 0

        for i in range(n):
            # Add prevoius prefix sum into SortedList
            # The first prefix sum is 0
            sort_pres.add(presum)

            # The current prefix sum
            presum += nums[i]

            # The lower limit in SortedList, should >= presum-upper
            left = sort_pres.bisect_left(presum-upper)
            # The upper limit in SortedList, should <= presum-lower
            right = sort_pres.bisect_right(presum-lower)
            # right - left is the count of sum of sub array which in 
            # distinct [lower, upper]
            ans += right - left

        return ans
    

    def countRangeSum_segtree(self, nums: List[int], lower: int, upper: int) -> int:
        '''segment tree
        '''
        from itertools import accumulate
        psums = list(accumulate(nums, initial=0))
        allNumber = set()
        for psum in psums:
            allNumber.add(psum)
            allNumber.add(psum-lower)
            allNumber.add(psum-upper)
    
        hvalue, initial  = {}, 0
        for num in allNumber:
            hvalue[num] = initial
            initial += 1
        
        import math
        tree = [-1] * (2 ** (math.ceil(math.log(len(allNumber), 2))+1) - 1)
        def build(l:int, r:int, p:int):
            if l == r:
                tree[p] = 0
            if r > l:
                mid = (l + r) // 2
                build(l, mid, p*2 +1)
                build(mid+1, r, p*2 +2)
                tree[p] = tree[p*2 + 1] + tree[p*2 + 2]
        
        def update(l:int, r:int, s:int, t:int, p:int):
            if l <= s and t <= r:
                tree[p] = 1
                return
            m = s + ((t - s) >> 1)
            if l <= m:
                update(l, r, s, m, p*2+1)
            if r > m:
                update(l, r, m + 1, t, p*2+2)
            tree[p] = tree[p*2+1] + tree[p*2+2]
        
        def query(l, r, s, t, p):
            if l <= s and t <= r:
                return tree[p]
            m = s + ((t - s) >> 1)
            count = 0
            if l <= m:
                count = query(l, r, s, m, p * 2 + 1)
            if r > m:
                sum = sum + query(l, r, m + 1, t, p * 2 + 2)
            return count
        


if __name__ == "__main__":
    sol = Solution()
    nums, lower, upper = [-2,5,-1], -2, 2
    print(sol.countRangeSum(nums, lower, upper))