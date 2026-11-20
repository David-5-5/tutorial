from math import gcd


class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        def reverse(i: int, j: int):
            while i < j:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
                j -= 1
        n = len(nums)
        k %= n
        reverse(0, n-1)
        reverse(0, k-1)
        reverse(k, n-1)
    
    def rotate2(self, nums: list[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k %= n
        if k == 0: return
        d = gcd(n, k)
        for i in range(d):
            start, val = i, nums[i]
            avail = start
            while True:
                x = (avail - k) % n
                if x == start: break
                nums[avail] = nums[x]
                avail = x
                
            nums[avail] = val
        