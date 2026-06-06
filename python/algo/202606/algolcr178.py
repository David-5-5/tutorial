from typing import Counter, List

// LCR series
class Solution:
    def trainingPlan(self, actions: List[int]) -> int:
        cnt = Counter(actions)
        for k, v in cnt.items():
            if v == 1: return k
        