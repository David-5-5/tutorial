from bisect import bisect_right
from typing import List


class Solution:
    def countComponents(self, nums: List[int], threshold: int) -> int:
        ans = n = len(nums)
        adt = [-1] * (n + 1)
        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]
        
        # dict num:inx
        ids = {x: i for i, x in enumerate(nums)}

        for g in range(1, threshold+1):
            f_x = -1
            for x in range(g, threshold+1, g):
                if x in ids.keys():
                    f_x = find(ids[x])
                    break
            
            if f_x < 0: continue

            for y in range(x + g, g * threshold // x + 1, g):
                if y in ids.keys():
                    f_y = find(ids[y])
                    if f_y != f_x:
                        adt[f_y] = f_x
                        ans -= 1

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, threshold = [2,4,8,3,9,12], 10
    print(sol.countComponents(nums, threshold))
