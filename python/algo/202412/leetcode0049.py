from collections import defaultdict
from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # 自行解答，可以用于 3272 题中，避免重复计算
        h = defaultdict(list)

        for s in strs:
            key = "".join(sorted(s))
            h[key].append(s)
        return list(h.values())    

