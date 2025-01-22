from collections import Counter


class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        cnt1, cnt2 = Counter(word1), Counter(word2)

        key1, key2 = list(cnt1.keys()), list(cnt2.keys())
        val1, val2 = list(cnt1.values()), list(cnt2.values())

        key1.sort(), key2.sort(), val1.sort() , val2.sort()

        return key1 == key2 and val1 == val2
