from typing import List

# 周赛 339
class Solution:
    def miceAndCheese(self, reward1: List[int], reward2: List[int], k: int) -> int:
        # 自行解答 reward1 - reward2 的差 倒序排序
        n = len(reward1)
        if n == k: return sum(reward1)

        diff = [reward2[i] - reward1[i] for i in range(n)]
        reversed, ans = k, 0
        for r1, r2, _ in sorted(zip(reward1, reward2, diff), key=lambda p:p[2]):
            if reversed:
                ans += r1
                reversed -= 1
            else: ans += r2
        return ans

if __name__ == "__main__":
    sol = Solution()
    reward1, reward2, k = [1,1,3,4], [4,4,1,1], 2
    print(sol.miceAndCheese(reward1, reward2, k))