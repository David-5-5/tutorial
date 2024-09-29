from collections import Counter
from typing import List

# 周赛 339
class Solution:
    def findMatrix(self, nums: List[int]) -> List[List[int]]:
        cnt = Counter(nums)

        ans = []
        while cnt:
            ans.append(list(cnt.keys()))
            for x in ans[-1]:
                if cnt[x] > 1:
                    cnt[x] -= 1
                else: del cnt[x]
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,3,4,1,2,3,1]
    print(sol.findMatrix(nums))