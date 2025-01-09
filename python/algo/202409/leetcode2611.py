from typing import List

# 周赛 339
class Solution:
    def miceAndCheese(self, reward1: List[int], reward2: List[int], k: int) -> int:
        # 自行解答 reward1 - reward2 的差倒序排序

        # 2025.1. 复习，补充思路
        # reward1[i1] + reward1[i2] + ...+ reward[ik]  + reward2[j1] + ... + reward2[jm] 为最大值
        # 假设 ik 与 jm 互换，则有:
        # reward1[i1] + reward1[i2] + ...+ reward1[ik]  + reward2[j1] + ... + reward2[jm]
        #  > reward1[i1] + reward1[i2] + ...+ reward1[jm]  + reward2[j1] + ... + reward2[ik]
        # 消除相同项:
        #   reward1[ik] + reward2[jm] > reward1[jm] + reward2[ik]
        #   reward1[ik] - reword2[ik] > reward1[jm] - reward2[jm]
        # 第一只老鼠优选选择 reward1[x] - reword2[x] 大的项
        # 通过结论反推 选择项目与 reward1, reward2 数组的关系
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