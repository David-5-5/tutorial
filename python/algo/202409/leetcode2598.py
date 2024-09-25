from collections import defaultdict
from typing import List

# 周赛 337
class Solution:
    def findSmallestInteger(self, nums: List[int], value: int) -> int:
        cnt = defaultdict(int)
        for v in nums:
            cnt[v%value] += 1
        ans = 0
        while True:
            if cnt[ans%value] == 0: break
            cnt[ans%value] -= 1
            ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, value = [1,-10,7,13,6,8], 5
    print(sol.findSmallestInteger(nums, value))