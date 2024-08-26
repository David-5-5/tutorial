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
    
    def findArray2(self, pref: List[int]) -> List[int]:
        ans = []

        pref = [0] + pref
        for i in range(1, len(pref)):
            ans.append(pref[i]^pref[i-1])
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    pref = [5,2,0,3,1]
    print(sol.findArray(pref))
    print(sol.findArray2(pref))