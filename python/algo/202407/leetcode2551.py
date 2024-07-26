from typing import List

# 周赛330
# k个背包，因此选择 k-1 个分割点，分割点的左右都会在不同的背包中。weights的左右两个端点都会选择，并会约掉
# 因此将每个分割点左右相加，并排序，取最大的 k - 1 个分割点和减去最小的 k - 1 个分割点和，即为结果
class Solution:
    def putMarbles(self, weights: List[int], k: int) -> int:
        n = len(weights)
        for i in range(n-1):
            weights[i] += weights[i+1]

        weights.pop() # 多余的 weight[-1] 不需要
        weights.sort()

        return sum(weights[len(weights)-k+1:]) - sum(weights[:k-1])


if __name__ == "__main__":
    sol = Solution()
    weights, k = [1,3,5,1], 2
    print(sol.putMarbles(weights, k))