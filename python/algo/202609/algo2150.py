from typing import Counter, List


class Solution:
    def findLonely(self, nums: List[int]) -> List[int]:
        cnt = Counter(nums)
        uniq = set(nums)

        ans = []
        for v in uniq:
            if cnt[v] > 1 or v-1 in uniq or v+1 in uniq:
                continue
            ans.append(v)
        return ans