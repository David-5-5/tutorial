from bisect import bisect_right


class Solution:
    def search(self, nums: list[int], target: int) -> bool:
        
        def check(l: int, r:int) -> bool:
            if nums[l] == target or nums[r] == target: return True
            if l == r: return nums[l] == target

            mid = (l + r) // 2
            if nums[mid] == target or nums[mid+1] == target: return True

            
            if nums[l] < target < nums[mid]:
                idx = bisect_right(nums[l:mid+1], target)
                return idx and nums[l+idx-1] == target
            else:
                if check(l, mid): return True
            
            if nums[mid+1] < target < nums[r]:
                idx = bisect_right(nums[mid+1:r+1], target)

                return idx and nums[mid + idx] == target
            else: return check(mid+1, r)

        return check(0, len(nums)-1)