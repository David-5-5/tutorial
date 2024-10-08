from functools import reduce
from operator import xor
from typing import List

# 周赛 344
class Solution:
    def doesValidArrayExist(self, derived: List[int]) -> bool:
        # 自行解答 derived[i] = original[i] ^ original[i + 1]
        # derived[0] ^ derived[1] .. ^ derived[n-2] ^ derived[n-1]
        # = original[0] ^ original[1] ^ original[1] ^ original[2] ... ^ original[n-2] ^ original[n-1] ^ original[n-1] ^ original[0]
        # = (original[0] ^ original[0]) ^ (original[1] ^ original[1]) ... ^ (original[n-1] ^ original[n-1])
        # = 0
        return reduce(xor, derived) == 0


if __name__ == "__main__":
    sol = Solution()
    derived = [1,1,0]
    print(sol.doesValidArrayExist(derived))