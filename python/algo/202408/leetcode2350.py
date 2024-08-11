from typing import List

# 双周赛 83 脑筋急转弯
class Solution:
    def shortestSequence(self, rolls: List[int], k: int) -> int:
        ans = 0
        kset = set()
        for v in rolls:
            kset.add(v)
            if len(kset) == k:
                ans += 1
                kset = set()
        return ans + 1
    
    def shortestSequence2(self, rolls: List[int], k: int) -> int:
        ans, l = 0, [i for i in range(1, k+1)]
        kset = set(l)
        for v in rolls:
            kset.remove(v)
            if len(kset) == 0:
                ans += 1
                kset = set(l)
        return ans + 1

if __name__ == "__main__":
    sol = Solution()
    rolls, k = [1,1,2,2], 2
    print(sol.shortestSequence(rolls, k))