from math import gcd, isqrt
from typing import List


# 解题思路 ： 质因子分解，区间合并

N = 10**6+1
min_prime_factor = [i for i in range(N)] 

for i in range(2, isqrt(N)+1):
    if min_prime_factor[i] == i:
        for j in range(i*i, N, i):
            min_prime_factor[j] = i

class Solution:
    def findValidSplit(self, nums: List[int]) -> int:
        # time limit exceeded
        n = len(nums)
        suffix_product = 1
        for i in range(n):
            suffix_product *= nums[i]
        
        ans = -1
        prefix_product = 1
        for i in range(n-1):
            prefix_product *= nums[i]
            suffix_product //= nums[i]
            if gcd(prefix_product,suffix_product) == 1:
                return i

        return ans

    def findValidSplit2(self, nums: List[int]) -> int:
        # [6,...,2,...3], 6, 2, 3 的下标分别为0 < i < j
        # left = {2:0, 3:0}
        # 遍历到 2 时, right[0] = i, 遍历到 3 时，重新赋值 right[0] = j, 
        left = {} # left[p] 表示质数 p 首次出现的下标
        right = [-1] * len(nums) # right[i] 表示左端点为 i 的区间的右端点的最大值
        
        def prime(i:int, inx:int):
            while min_prime_factor[i] > 1:
                if min_prime_factor[i] in left:
                    right[left[min_prime_factor[i]]] = inx
                else:
                    left[min_prime_factor[i]] = inx
                i = i // min_prime_factor[i]
            
        for inx, i in enumerate(nums):
            prime(i, inx)
        
        max_r = 0
        for l, r in enumerate(right): # l 自动排序
            if l > max_r:
                return max_r # l - 1
            else:
                max_r = max(max_r, r)
        return -1


if __name__ == "__main__":
    sol = Solution()
    nums = [4,7,15,8,3,5]
    nums = [1,1,89]
    print(sol.findValidSplit2(nums))