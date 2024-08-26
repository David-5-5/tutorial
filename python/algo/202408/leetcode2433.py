from typing import List

# 周赛 314
class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        ans = []

        prev = 0
        for p in pref:
            ans.append(p ^ prev)
            prev = p
        return ans

if __name__ == "__main__":
    sol = Solution()
    pref = [5,2,0,3,1]
    print(sol.findArray(pref))