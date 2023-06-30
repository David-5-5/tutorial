from functools import lru_cache
from re import M


class Solution:
    def longestDecomposition(self, text: str) -> int:

        @lru_cache(maxsize=None)
        def decomposition(subtext:str) -> int :
            n = len(subtext)
            if len(subtext) == 0 :return 0
            if len(subtext) == 1 :return 1

            findI = subtext.find(subtext[0], n // 2)
            longest = 0
            while findI != -1:
                for i in range(findI, n):
                    if subtext[i-findI] != subtext[i]:
                        longest = max(longest, 1)
                        break;
                else:
                    longest = max(longest, 2 + decomposition(subtext[n-findI:findI]))
                findI = subtext.find(subtext[0], findI + 1)
                
            longest = max(longest, 1)
            return longest

        return decomposition(text)


if __name__ == "__main__":
    sol = Solution()
    print(sol.longestDecomposition("aaaaaaaaaaaaaaaaaaaaaa"))