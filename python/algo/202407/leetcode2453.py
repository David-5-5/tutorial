from collections import defaultdict
from math import inf
from typing import List

# 双周赛 90
class Solution:
    def destroyTargets(self, nums: List[int], space: int) -> int:
        cnt = {}
        nums.sort(reverse=True)
        maxcnt, ans = -1, max(nums)
        for num in nums :
            x = num%space
            if x not in cnt: cnt[x] = 0
            else:
                cnt[x] += 1
            if cnt[x] > maxcnt or cnt[x] == maxcnt and num < ans:
                ans = num
                maxcnt = cnt[x]

        return ans
    
    def destroyTargets2(self, nums: List[int], space: int) -> int:
        # 视频
        cnt = defaultdict(lambda: [0, inf])
        
        for num in nums :
            cnt[num%space] = [cnt[num%space][0]+1, min(cnt[num%space][1], num)]

        maxcnt, ans = -1, max(nums)
        for m,x in cnt.values() :

            if m > maxcnt or m == maxcnt and x < ans:
                maxcnt, ans = m, x

        return ans

        # The performance is best when using the following code.
        # cnt = defaultdict(list)
        
        # for num in nums :
        #     cnt[num%space].append(num)

        # maxcnt, ans = 0, 0
        # for a in cnt.values() :
        #     m = len(a)
        #     x = min(a)
        #     if m > maxcnt or m == maxcnt and x < ans:
        #         maxcnt, ans = m, x

        # return ans    

if __name__ == "__main__":
    sol = Solution()
    nums, space = [3,7,8,1,1,5], 2
    print(sol.destroyTargets(nums, space))
    print(sol.destroyTargets2(nums, space))