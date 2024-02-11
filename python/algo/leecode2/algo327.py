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
        for num in sorted(list(allNumber)):
            hvalue[num] = initial
            initial += 1
        
        import math
        # build the segment tree, it initial count is 0
        tree = [0] * (2 ** (math.ceil(math.log(len(allNumber), 2))+1) - 1)
        
        def update(value:int, s:int, t:int, p:int):
            tree[p] += 1
            if s == t:
                return
            m = s + ((t - s) >> 1)
            if value <= m:
                update(value, s, m, p*2+1)
            if value > m:
                update(value, m + 1, t, p*2+2)
        
        def query(l, r, s, t, p):
            if l <= s and t <= r:
                return tree[p]
            m = s + ((t - s) >> 1)
            count = 0
            if l <= m:
                count = query(l, r, s, m, p * 2 + 1)
            if r > m:
                count = count + query(l, r, m + 1, t, p * 2 + 2)
            return count

        ans = 0
        for i in range(len(psums)):
            left, right = hvalue[psums[i]-upper], hvalue[psums[i]-lower]
            ans += query(left, right, 0, len(allNumber)-1, 0)
            update(hvalue[psums[i]],0, len(allNumber)-1, 0)

        return ans

    def countRangeSum_dop_segtree(self, nums: List[int], lower: int, upper: int) -> int:
        '''dynamically open point segment tree
        动态开点线段树
        '''
        from itertools import accumulate
        psums = list(accumulate(nums, initial=0))
        
        # 二维数组，根节点为tree[0], 每个节点包含三个元素len(tree[i]) == 3
        # tree[i][0] count, tree[i][1] left child, tree[i][2] right child
        tree = []
        def update(value:int, s:int, t:int, p:int):
            tree[p] += 1
            if s == t:
                return
            m = s + ((t - s) >> 1)
            if value <= m:
                update(value, s, m, p*2+1)
            if value > m:
                update(value, m + 1, t, p*2+2)
        
        def query(l, r, s, t, p):
            if l <= s and t <= r:
                return tree[p]
            m = s + ((t - s) >> 1)
            count = 0
            if l <= m:
                count = query(l, r, s, m, p * 2 + 1)
            if r > m:
                count = count + query(l, r, m + 1, t, p * 2 + 2)
            return count

        ans = 0
        for i in range(len(psums)):
            left, right = psums[i]-upper, psums[i]-lower
            ans += query(left, right, 0, i, 0)
            update(psums[i],0, i, 0)

        return ans
if __name__ == "__main__":
    sol = Solution()
    nums, lower, upper = [-2,5,-1], -2, 2
    print(sol.countRangeSum(nums, lower, upper))
    print(sol.countRangeSum_dop_segtree(nums, lower, upper))