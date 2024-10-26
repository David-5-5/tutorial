
from typing import Counter


class Solution:
    def possibleStringCount(self, word: str) -> int:

        ans = 0
        prev = ''
        count = 1
        for v in word:
            if prev == v:
                count += 1
            else:
                if count: ans += count - 1
                count = 1
            prev = v
        
        ans += count - 1

        return ans + 1


if __name__ == "__main__":
    sol = Solution()
    print(sol.possibleStringCount("abbcccc"))