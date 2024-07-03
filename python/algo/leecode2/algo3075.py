from typing import List
class Solution:
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:
        happiness.sort(reverse=True)
        res = 0
        for i, x in enumerate(happiness[0:k]):
            if x - i <= 0:
                break
            res += x - i
        return res