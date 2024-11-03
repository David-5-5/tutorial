from collections import defaultdict
from typing import List

# 双周赛 132
class Solution:
    def findWinningPlayer(self, skills: List[int], k: int) -> int:
        cnt = defaultdict(int)

        cur = 0
        for i in range(1, len(skills)):
            if skills[i] > skills[cur]:
                cur = i
            cnt[cur] += 1
            if cnt[cur] == k: return cur
        return cur

if __name__ == "__main__":
    sol = Solution()
    skills, k = [2,5,4], 3
    print(sol.findWinningPlayer(skills, k))