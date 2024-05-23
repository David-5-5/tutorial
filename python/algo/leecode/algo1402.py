from itertools import accumulate
class Solution:
    # 思路:
    # 1 satisfaction[i] 越大，放到最后做，like-time 系数越高
    # 2 对于负值放到前面做，可以增加后续正值的 ith 值
    # 3 当前面的负值，不能增加总体 like-time 系数时，执行终止，当前值即为最大值
    def maxSatisfaction(self, satisfaction) -> int:
        satisfaction.sort();
        maxSatis = 0;
        lenght = len(satisfaction);
        for i in reversed(range(lenght)):
            if i !=  0 and satisfaction[i]>=0 :
                continue;
            cur = self.calculate(satisfaction[i:])
            if (cur > maxSatis):
                maxSatis = cur;
            else:
                return maxSatis
        return maxSatis
    def calculate(self, selected) -> int:
        satis = 0;
        for i in range(len(selected)):
            satis += (i + 1) * selected[i]
        return satis

    def maxSatisfaction2(self, satisfaction) -> int:
        # 思路与上面一直，使用前缀和，提升执行效率
        satisfaction.sort();
        maxSatis = 0;
        lenght = len(satisfaction);

        presum = list(accumulate(satisfaction, initial=0))
        for i in reversed(range(lenght)):
            cur = maxSatis + presum[lenght] - presum[i]
            if (cur > maxSatis):
                maxSatis = cur
            else:
                return maxSatis
        return maxSatis


if __name__ == "__main__":
    sol = Solution()
    satisfaction = [-1,-8,0,5,-9]
    print(sol.maxSatisfaction2(satisfaction))