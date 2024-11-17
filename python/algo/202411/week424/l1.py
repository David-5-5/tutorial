from typing import List


class Solution:
    def countValidSelections(self, nums: List[int]) -> int:
        ans = prefix = 0
        ss = sum(nums)

        for v in nums:
            prefix += v
            if prefix * 2 == ss and v == 0 :
                ans += 2
            if (prefix * 2 == ss - 1 or prefix * 2 == ss + 1) and v == 0:
                ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()

    print(sol.countValidSelections([16,13,10,0,0,0,10,6,7,8,7]))