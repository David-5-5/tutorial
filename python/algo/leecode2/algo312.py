from functools import lru_cache
class Solution:
    def maxCoins(self, nums) -> int:
        n = len(nums)
        val = [1] + nums + [1]
        
        @lru_cache(maxsize = None)
        def subCoins(left, right):
            if left >= right-1:
                return 0
            
            ret = 0
            for i in range(left+1, right):
                cur = val[left] * val[i] * val[right]
                cur += subCoins(left, i) + subCoins(i, right)
                ret = max(ret, cur)
            return ret
        return subCoins(0, n+1)

if __name__ == "__main__":
    sol = Solution()
    nums = [3,1,5,8]
    print(sol.maxCoins(nums))