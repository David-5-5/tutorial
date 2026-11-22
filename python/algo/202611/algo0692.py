import heapq
from typing import Counter


class Solution:
    def topKFrequent(self, words: list[str], k: int) -> list[str]:
        # python heapq.nsmallest
        # 双因子排序，通过负号，让两个因子同方向
        cnt = [(-c, word) for word, c in Counter(words).items()]
        return [word for _, word in heapq.nsmallest(k, cnt)]