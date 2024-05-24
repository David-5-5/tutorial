from typing import List
from bisect import bisect_right
class Solution:
    def minimumDeviation(self, nums: List[int]) -> int:
        nums.sort()
        res = nums[-1] + 1
        inx = 0
        while nums[inx] % 2 == 1 and inx+1 < len(nums):
            res = min(res, max(nums[-1], 2*nums[inx]) - nums[inx+1])
            inx += 1 

        inx = len(nums) - 1
        while nums[inx] % 2 == 0 and inx > 0:
            res = min(res, nums[inx-1] - min(nums[0], nums[inx]//2))
            inx -= 1 

        loop = []
        change = True
        while change and res>0:
            res = min(res, nums[-1] - nums[0])

            if nums[-1] % 2 == 0 and (nums[0] % 2 == 0 or max(nums[-2]-nums[0], nums[-2]-nums[-1]//2) < max(nums[-1]-nums[1], 2*nums[0]-nums[1])):
                div = nums.pop(-1) // 2
                inx = bisect_right(nums, div)
                nums.insert(inx, div)
                if inx == 0: loop.append(div)
            elif nums[0] % 2 == 1:
                mul = nums.pop(0) * 2
                inx = bisect_right(nums, mul)
                nums.insert(inx, mul)
                if inx+1 == len(nums): loop.append(mul)
            else:
                change = False

            if len(loop) == 3 and loop[0] == loop[2]:
                return res
            elif len(loop) == 3:
                loop.pop(0)

        return res
    
    def minimumDeviation2(self, nums: List[int]) -> int:
        nums.sort()
        res = nums[-1] + 1
        while res > nums[-1] - nums[0]:
            res = nums[-1] - nums[0]

            if nums[-1] % 2 == 0:
                div = nums.pop(-1) // 2
                inx = bisect_right(nums, div)
                nums.insert(inx, div)
            
            if nums[0] % 2 == 1:
                mul = nums.pop(0) * 2
                inx = bisect_right(nums, mul)
                nums.insert(inx, mul)

        return res   
if __name__ == "__main__":
    sol = Solution()
    nums = [100006875, 100009557, 100085011, 100156725, 100199892, 100211652, 100261757, 100275031, 100322578, 100324729, 100330645, 100341912, 100343078, 100367446, 100384366, 100404186, 100417232, 100581588, 100611117, 100686954, 199433768, 199471414, 199494095, 199559817, 199583910, 199717348, 199736048, 199749556, 199757855, 199762309, 199825000, 199857056, 199863014, 199867151, 199929782, 199933217, 199941995, 199969885, 199973064, 199994746]
    print(sol.minimumDeviation(nums))
