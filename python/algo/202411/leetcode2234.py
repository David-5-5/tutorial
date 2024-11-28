from itertools import accumulate
from typing import List

# 贪心专题 先枚举，再贪心
class Solution:
    def maximumBeauty(self, flowers: List[int], newFlowers: int, target: int, full: int, partial: int) -> int:
        # 自行思考：
        #   枚举 逐渐提高最小值后，可以填充多少完善花园
        #        需要填充的完善花园可以按照需要填充的数量从小到大排序，并计算前缀和
        #        但每次将最小值加 1 后，需要填充的前缀和重新计算，最差情况下 时间复杂度 O(n^2)
        # 参考题解:
        #   将flower排序后，将所有的flower预填充为target，然后枚举，将填充逐渐减少，
        #   并逐步增加最小值
        # 总结，有基本的思路，但是代码写不出来。题解的思路是反向枚举填充，逐步计算前缀和并填充left，计算平均值
        n = len(flowers)
        flowers.sort()
        if flowers[0] >= target: return full * n

        rest = newFlowers - target * n
        for i in range(n):
            flowers[i] = min(flowers[i], target)
            rest += flowers[i]

        # 初始化返回值
        ans = x = preSum = 0

        for i in range(n+1): # 包括后缀为 0 的情况
            if rest >= 0:
                while x < i and flowers[x]*x - preSum <= rest:
                    preSum += flowers[x]
                    x += 1
                beauty = (n - i) * full
                if x:
                    beauty += min((preSum+rest)//x, target-1) * partial
                ans = max(ans, beauty)
            if i < n:
                rest += target - flowers[i]
        return ans

if __name__ == "__main__":
    sol = Solution()
    flowers, newFlowers, target, full, partial = [1,3,1,1], 7 ,6 ,12, 1
    print(sol.maximumBeauty(flowers, newFlowers, target, full, partial))