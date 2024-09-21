from functools import cache
from typing import List


class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        # 自行解答，记忆化搜索
        n = len(nums)
        score = 0 
        @cache
        def dfs(l:int, r:int) -> int:
            nonlocal score
            if l >= r : return 0
            if l+1 == r:
                if nums[l]+nums[r] == score:
                    return 1
                else: return 0

            res = 0
            if nums[l] + nums[l+1] == score: res = 1 + dfs(l+2, r)
            if nums[l] + nums[r] == score : res = max(res, 1 + dfs(l+1, r-1))
            if nums[r] + nums[r-1] == score: res = max(res, 1 + dfs(l, r-2))
            return res

        score = nums[0] + nums[1]
        ans = dfs(2, n-1)
        score = nums[0] + nums[-1]
        ans = max(ans, dfs(1, n-2))
        score = nums[-2] + nums[-1]
        ans = max(ans, dfs(0, n-3))

        return ans + 1

    def maxOperations2(self, nums: List[int]) -> int:
        # 自行解答，记忆化搜索,简化
        n = len(nums)
        score = list(set([nums[0]+nums[1], nums[0]+nums[-1], nums[-2]+nums[-1]]))
        @cache
        def dfs(l:int, r:int, sw:int) -> int:
            if l >= r : return 0
            if l+1 == r:
                if nums[l]+nums[r] == score[sw]:
                    return 1
                else: return 0

            res = 0
            if nums[l] + nums[l+1] == score[sw]: res = 1 + dfs(l+2, r, sw)
            if nums[l] + nums[r] == score[sw] : res = max(res, 1 + dfs(l+1, r-1, sw))
            if nums[r] + nums[r-1] == score[sw]: res = max(res, 1 + dfs(l, r-2, sw))
            return res
        
        return max(dfs(0,n-1,sw) for sw in range(len(score)))

if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,1,2,3,4]
    print(sol.maxOperations2(nums))