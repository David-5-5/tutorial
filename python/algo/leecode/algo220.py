class Solution:
    def containsNearbyAlmostDuplicate(self, nums, indexDiff: int, valueDiff: int) -> bool:
        if len(nums) == 0 : return 0
        n = len(nums)
        numInx = {}
        for i in range(n):
            bin = nums[i] // (valueDiff + 1)
            if bin in numInx:
                inx = numInx.get(bin)
                if abs(inx - i) <= indexDiff:
                    return True
            if (bin - 1) in numInx:
                inx = numInx.get(bin - 1)
                if abs(nums[inx]-nums[i])<= valueDiff and abs(inx-i)<=indexDiff:
                   return True
            if (bin + 1) in numInx:
                inx = numInx.get(bin + 1)
                if abs(nums[inx]-nums[i])<= valueDiff and abs(inx-i)<=indexDiff:
                   return True
            numInx[bin] = i
        return False

if __name__ == "__main__":
    sol = Solution()
    nums = [1,5,9,1,5,9]
    # import random
    # nums = [random.randint(1,20000) for _ in range(1234)]
    from datetime import datetime
    begin = datetime.now()
    print(sol.containsNearbyAlmostDuplicate(nums, 10000, 0))
    print((datetime.now()- begin).total_seconds())
