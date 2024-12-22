from collections import defaultdict
from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # 自行解答，可以用于 3272 题中，避免重复计算
        h = defaultdict(list)

        for str in strs:
            key = "".join(sorted(str))
            h[key].append(str)
        return list(h.values())    

