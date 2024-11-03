from collections import defaultdict
from typing import List

# 双周赛 132
class Solution:
    def findWinningPlayer(self, skills: List[int], k: int) -> int:
        # 自行解答
        cnt = defaultdict(int)

        cur = 0
        # 一次遍历，选出最大值
        for i in range(1, len(skills)):
            if skills[i] > skills[cur]:
                cur = i
            cnt[cur] += 1
            if cnt[cur] == k: return cur
        # 后续的胜出者，只能是最大值 k = 10 ^ 9 是个陷阱
        return cur

if __name__ == "__main__":
    sol = Solution()
    skills, k = [2,5,4], 3
    print(sol.findWinningPlayer(skills, k))