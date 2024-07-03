from typing import List

class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        # 贪心算法，从最右边的一对叶子结点开始遍历, 因此起始 n-2，
        # 求最小的更新次数，因此更新子结点不如更新父结点
        # 同一父结点的两个相邻的兄弟结点更新其差值即可(最小次数)，
        # 并将更新后的值增加到父结点的cost当中
        ans = 0
        for i in range(n-2, 0, -2):
            # cost 结点编号从 0 开始
            # i 和 i+1 为兄弟结点, i//2 为 i 和 i+1的父结点
            ans += abs(cost[i]-cost[i+1])
            cost[i//2] += max(cost[i], cost[i+1])
        return ans


if __name__ == "__main__":
    sol = Solution()
    n, cost = 7, [1,5,2,2,3,3,1]
    print(sol.minIncrements(n, cost))    